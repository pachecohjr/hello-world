
/*
Cache Simulator
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>
#include <regex>

using namespace std;

//Structure to model the blocks

struct block{
  bitset<32> startAddress;
  int tag;
  bool isValid;
  int timeStamp;
};

//Structure for hit

struct readReturn{
  bool isHit;
  int hitWay;
  string tag;
  int index;
  int offset;
};

//Structure to bundle the eviction data. Contains information if the write leads
//to an eviction or not.
//and if it does, returns the evicted block.

struct writeReturn{
  bool isEvicted;
  block evictedBlock;
  int writeWay;

  string tag;
  int index;
  int offset;
};

int btoi(string s);

/* A data structure modelling the cache
 */
class cache{

  //Given Attributes of a cache
  unsigned int numSets;    //Number of sets
  unsigned int setSize;    //Number of ways
  unsigned int lineSize;   //Number of blocks in a set


  //To be computed attributes from the given data
  unsigned int ways;

  unsigned int tag_length;
  unsigned int index_length;
  unsigned int offset_length;

  //Variable to keep track of the access
  unsigned int time;

  vector<block> blocks;

  int hitCount;
  int missCount;

  //constructor
public:
  cache(unsigned int num_Sets, unsigned int set_Size, unsigned int line_Size){

    //Increment time in main method.
    time = 0;
    hitCount = 0;
    missCount = 0;
    //Initializing values
    numSets = num_Sets;
    setSize = set_Size;
    lineSize = line_Size;

    ways = set_Size;

    //Number of blocks = Number of ways * Number of sets * line size
    blocks.resize(num_Sets*set_Size*line_Size);

    //Number of bits required for offset, index and tag
    offset_length = log2(lineSize);
    index_length = log2(numSets);
    tag_length = 32 - offset_length - index_length;
    //cout<<offset_length<<" "<<index_length<<" "<<tag_length<<" ";

    //Invalidate all the cache blocks. Done here in a set first basis

    for(int i=0; i<setSize; i++){
      for(int j=0; j<ways; j++){
        for(int k=0; k<lineSize; k++){
          blocks[((i*ways)+j)*lineSize+k].isValid = false;
          blocks[((i*ways)+j)*lineSize+k].tag = -1;
        }
      }
    }

    //Done with constructor. So all the parameters of the cache have been set.
  }


  //Operations a cache can perform.

  //A cache can be read or written.
  //Here are the helper methods which help you do so.
  //These helper methods are basically dumb and they read or write without
  //actually checking any condition
  //and do not make any changes to the cache.
  //These conditions should be handled in the main method when these methods are
  //accessed.


  //The Read method checks if the passed address is present in the cache
  //and returns an object of type 'hit' which contains the info if it is a hit
  //or not.
  //And also the way in which it was a hit if it was a hit.

  readReturn Read(bitset<32> address){

    string addressString = address.to_string();
    string tagString = addressString.substr(0,tag_length);
    string indexString = addressString.substr(tag_length,index_length);
    string offsetString = addressString.substr(32-offset_length,offset_length);

    int tagValue = btoi(tagString);
    int indexValue = btoi(indexString);
    int offsetValue = btoi(offsetString);

    //The offset bits are simply ignored because it is enough if we look for the
    //start address of the block

    readReturn h;

    //Initializing the hit object to 'false'
    //The address is searched for in the cache. If it found, it is set to
    //true. If not it is simply returned as
    //it is without updating.

    h.isHit = false;
    h.hitWay = -1;
    h.index = indexValue;
    h.offset = offsetValue;
    stringstream stream;
    stream << hex << tagValue;
    h.tag = stream.str();

    //Search in each way of the set at the calculated index.
    for(int i=0; i<ways; i++){
      //The block 'current' is the block in focus for this iteration.
      //I'm assuming that the blocks are laid in set-first basis.
      block current = blocks[((indexValue*ways)+i)*lineSize+offsetValue];

      //The 'startAddress' variable of each block contains the address of the
      //first block of the data it contains.
      //The tag can be extracted from this address.

      //            string currentTag =
      //            current.startAddress.to_string().substr(0,tag);
      if(current.isValid){
        if(current.tag == tagValue){
          h.isHit = true;
          h.hitWay = i;
          break;
        }
      }
    }
    return h;
  }


  //The write method writes into the cache at the passed address no matter what.
  //It returns information if the write has lead to an eviction or not.

  writeReturn Write(bitset<32> address){

    writeReturn w;

    string addressString = address.to_string();
    string tagString = addressString.substr(0,tag_length);
    string indexString = addressString.substr(tag_length,index_length);
    string offsetString = addressString.substr(32-offset_length,offset_length);

    int tagValue = btoi(tagString);
    int indexValue = btoi(indexString);
    int offsetValue = btoi(offsetString);

    w.offset = offsetValue;
    w.index = indexValue;

    stringstream stream;
    stream << hex << tagValue;
    w.tag = stream.str();

    addressString = tagString+indexString+offsetString;

    block temp;
    temp.isValid = true;
    temp.tag = tagValue;
    temp.startAddress = bitset<32> (addressString);
    readReturn h = Read(address);
    //Check if the address to be written is present in the cache
    //If it is present just update the data.
    if(h.isHit){
      //We aren't handling data. So nothing to do
      //int hitWay = h.hitWay;
      //blocks[((indexValue*ways)+hitWay)*lineSize+offsetValue] = temp;
      w.isEvicted = false;
      w.writeWay = h.hitWay;
      return w;
      //Should break.....

    }
    //Else Check if any of the blocks in the set is empty
    else{
      for(int i=0; i<ways; i++){
        //If any of the blocks in the set is invalid, it means it is empty
        if(!blocks[((indexValue*ways)+i)*lineSize+offsetValue].isValid){
          blocks[((indexValue*ways)+i)*lineSize+offsetValue] = temp;
          //There is an empty block in the set. Hence no need to evict data
          w.isEvicted = false;
          w.writeWay = i;
          return w;
        }
      }
    }
    //If both fail, the set is full and data needs to be evicted
    int lruWay = 0;

    for(int i=1; i<ways; i++){
      if(blocks[((indexValue*ways)+i)*lineSize+offsetValue].timeStamp < blocks[((indexValue*ways)+lruWay)*lineSize+offsetValue].timeStamp){
        lruWay = i;
      }
    }
    int evictionWay = lruWay;
    block evictedBlock = blocks[((indexValue*ways)+evictionWay)*lineSize+offsetValue];
    blocks[((indexValue*ways)+evictionWay)*lineSize+offsetValue] = temp;
    w.writeWay = lruWay;
    w.evictedBlock = evictedBlock;
    w.isEvicted = true;
    return w;
  }

  //Function to set the timestamp for a block to do the LRU
  void setTimeStamp(bitset<32> address, int updateWay, int time){
    string addressString = address.to_string();
    string tagString = addressString.substr(0,tag_length);
    string indexString = addressString.substr(tag_length,index_length);
    string offsetString = addressString.substr(32-offset_length,offset_length);

    int tagValue = btoi(tagString);
    int indexValue = btoi(indexString);
    int offsetValue = btoi(offsetString);

    blocks[((indexValue*ways)+updateWay)*lineSize+offsetValue].timeStamp = time;

  }

  void incrementHitCount(){
    hitCount++;
  }

  void incrementMissCount(){
    missCount++;
  }

  int getHitCount(){
    return hitCount;
  }

  int getMissCount(){
    return missCount;
  }
};

bool isValidSize(int size){
  if(size == 1){
    return true;
  }
  else if(size == 2)
    return true;
  else if(size == 4)
    return true;
  else if(size == 8)
    return true;
  return false;

}

void accessCache(cache *myCache, char accessType, int size, string hexAddress, int accessTime){
  if(!isValidSize(size)){
    cout << "Warning: Invalid reference size."<<endl;
    return;
  }
  //convert hex address to bitset
  istringstream ss(hexAddress);
  unsigned long decimalAddress;
  ss >> hex >> decimalAddress;
  bitset<32> address(decimalAddress);

  if(accessType == 'R'|| accessType == 'r'){
    //Try to read from the cache
    readReturn readReturn1 = myCache->Read(address);
    //If the read was hit, then update the timeStamp
    if(readReturn1.isHit){
      myCache->incrementHitCount();
      myCache->setTimeStamp(address,readReturn1.hitWay,accessTime);
    }
    //If it was a miss, fetch from memory and make it available
    else{
      writeReturn w = myCache->Write(address);
      myCache->incrementMissCount();
      myCache->setTimeStamp(address,w.writeWay,accessTime);
    }
    string isHit = readReturn1.isHit?"hit":"miss";
    int memRef = readReturn1.isHit?0:1;
    //cout << "  read " <<hexAddress << " " <<readReturn1.tag << "
    //"<<readReturn1.index<<" " << readReturn1.offset<<" " << isHit<<" " <<
    //memRef;
    cout << setw(6) << "read";
    cout << setw(9) << hexAddress;
    cout << setw(7) << readReturn1.tag;
    cout << setw(6) << readReturn1.index;
    cout << setw(7) << readReturn1.offset;
    cout << setw(7) << isHit;
    cout << setw(8) << memRef;

    cout<<endl;
  }
  else if(accessType == 'W' || accessType == 'w'){
    //Check if the address is already present
    readReturn readReturn1 = myCache->Read(address);
    if(readReturn1.isHit){
      //If the address is present in the cache, just update the time stamp
      myCache->incrementHitCount();
      myCache->setTimeStamp(address,readReturn1.hitWay,accessTime);
    }
    //If the address is not present in the cache, we have to write it into the
    //cache
    else{
      writeReturn w = myCache->Write(address);
      myCache->incrementMissCount();
      myCache->setTimeStamp(address,w.writeWay,accessTime);
    }
  }
  else{
    return;
  }
}
int main(int argc, char* argv[]){
  //int main(){

  int currentTime = 0;
  ifstream cache_config;
  ifstream traces;
  string dummyLine;
  size_t x;
  //cache_params.open(argv[1]);

  cache_config.open(argv[1]);
  traces.open(argv[2]);

  //cache_config.open("C:\\Users\\My PC\\Desktop\\Jeff\\trace.config");
  //traces.open("C:\\Users\\My PC\\Desktop\\Jeff\\trace.dat");

  int i=0;
  int num_sets = 0;
  int set_size = 0;
  int line_size = 0;
  for(string line; getline(cache_config, line); ){
    x = line.find(":");
    if(x!=line.npos && i==0){
      //'x' has the index of ':'. We need to start reading from the next
      //character
      string num = line.substr(x+1);
      num_sets = atoi(num.c_str());
    }
    else if(x!=line.npos && i==1){
      string num = line.substr(x+1);
      set_size = atoi(num.c_str());
    }
    else if(x!=line.npos && i==2){
      string num = line.substr(x+1);
      line_size = atoi(num.c_str());
    }
    else{
      cout << "Invalid configuration file. Exiting..."<<endl;
      return 0;
    }
    i++;
  }
  cache_config.close();

  cache *myCache = new cache(num_sets,set_size,line_size);
  //cache myCache(num_sets,set_size,line_size);
  string line;

  char accessType;
  int size;
  string address;
  //cout << "Access\tAddress\tTag\tIndex\tOffset\tResult\tMemrefs"<<endl;
  cout << "Access Address    Tag   Index Offset Result Memrefs"<<endl;
  cout << "------ -------- ------- ----- ------ ------ -------"<<endl;

  for(; traces >> line; ){
    accessType = line.c_str()[0];
    size = atoi(line.substr(line.find(":")+1,line.find_last_of(":")-line.find(":")).c_str());
    address = line.substr(line.find_last_of(":")+1);
    accessCache(myCache, accessType, size, address, currentTime);
    currentTime++;
  }

  /*while(!traces.eof()){

    traces >> line;
        accessType = line.c_str()[0];
        size =
        atoi(line.substr(line.find(":")+1,line.find_last_of(":")-line.find(":")).c_str());
        address = line.substr(line.find_last_of(":")+1);
        accessCache(myCache, accessType, size, address, currentTime);
        currentTime++;

}*/
  int hitCount = myCache->getHitCount();
  int missCount = myCache->getMissCount();
  int totalAccesses = hitCount + missCount;
  double hitRatio = (double)hitCount/totalAccesses;
  double missRatio = (double) missCount/totalAccesses;

  cout << "\nSimulation Summary Statistics"<<endl;
  cout << "-----------------------------"<<endl;
  cout << "Total hits         : "<<hitCount<<endl;
  cout << "Total missed       : "<<missCount<<endl;
  cout << "Total accesses     : "<<totalAccesses<<endl;
  cout << "Hit ratio          : "<<fixed << setprecision(6)<<hitRatio<<endl;
  cout << "Miss ratio         : "<<fixed << setprecision(6)<<missRatio<<endl;
  traces.close();
  return 0;
}

int btoi(string s){
  int integerValue = 0;
  int length = s.size();
  int k;
  for(int i=0; i<length; i++){
    char c = s[(length-1)-i];
    if(c == '0')
      k = 0;
    else
      k = 1;
    integerValue = integerValue + k * pow(2,i);
  }
  return integerValue;
}
