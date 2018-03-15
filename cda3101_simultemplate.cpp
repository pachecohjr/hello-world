/******************************************************
 *                                                     *
 *       Name: Humphrey J. Pachecker                   *
 *      Class: CDA 3101                                *
 * Assignment: Asg 3 (a simulator for a subset of the  *
 *                    MIPS assembly language           *
 *    Compile: "clang++ -std=c++11"                    *
 *                                                     *
 ******************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

#define MAXLINE 80
#define MAXREG  5
#define MAXLINELENGTH 100
#define MAXINSTRUCTIONS 32768

// We can remove the 2nd column altogether 
// as improvement.
struct {
  const std::string name;
  int address;
} registerMap[32] = {
  { "zero", 0 },
  { "at", 1 },
  { "v0", 2 },
  { "v1", 3 },
  { "a0", 4 },
  { "a1", 5 },
  { "a2", 6 },
  { "a3", 7 },
  { "t0", 8 },
  { "t1", 9 },
  { "t2", 10 },
  { "t3", 11 },
  { "t4", 12 },
  { "t5", 13 },
  { "t6", 14 },
  { "t7", 15 },
  { "s0", 16 },
  { "s1", 17 },
  { "s2", 18 },
  { "s3", 19 },
  { "s4", 20 },
  { "s5", 21 },
  { "s6", 22 },
  { "s7", 23 },
  { "t8", 24 },
  { "t9", 25 },
  { "k0", 26 },
  { "k1", 27 },
  { "gp", 28 },
  { "sp", 29 },
  { "fp", 30 },
  { "ra", 31 } 
};

struct {
  const std::string name;
  int opcode;
  int funct;
} validOpCodes[] = {
  {"addiu",9},
  {"addu",0,0x21},
  {"and",0,0x24},
  {"beq",4},
  {"bne",5},
  {"div",0,0x1a},
  {"j",2},
  {"lw",0x23},
  {"mfhi",0,0x10},
  {"mflo",0,0x12},
  {"mult",0,0x18},
  {"or",0,0x25},
  {"slt",0,0x2a},
  {"subu",0,0x23},
  {"sw",0x2b},
  {"syscall",0,0xc},
  {".word",0}
};

/*const char *hexstring = "abcdef0";
  int number = (int)strtol(hexstring, NULL, 16);*/

union u {
  long int d;
  unsigned int x;
  struct {
    unsigned int funct:6;
    unsigned int shamt:5;
    unsigned int rd:5;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
  } r;
  struct {
    long int immed:16;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
  } i;
  struct {
    unsigned int pseudo_absolute:26;
    unsigned int opcode:6;
  } j;
};

typedef union u u;

struct instruct{
  unsigned int opcode,rs,rt,rd,shamt,funct;
  long int immed;
  long int segmentOffset;
  long int segmentNumber;
  int format;
  int type;
};

 enum Format { FORMAT_NA, R_FORMAT, I_FORMAT, J_FORMAT };
 enum Type   { TYPE_NA, ALU, LOAD, STORE, BRANCH, JUMP, OTHER };

/* typedef struct mips_inst {
  string name;
  operation issyscall;
  const byte format;
  const byte opcode;
  const byte type;
  const byte numArgs;
  const bool reg_writes; 
  const byte alu_src; // 0: src from reg, 1: src from immed, 2: src frm both
} instructionList; */

typedef unsigned int word;

/* const instructionList instructList[15] = 
  {
    { "addiu", NULL, I_FORMAT, 9, ALU, NULL, true, 1 },
    { "addu",  NULL, R_FORMAT, ALU, 3, true, 0 }, 
    { "and",   NULL, R_FORMAT, ALU, 3, true, 0 },
    { "beq",   NULL, I_FORMAT, BRANCH, NULL, false, 0 },
    { "bne",   NULL, I_FORMAT, BRANCH, NULL, false, 0 },
    { "div",   NULL, R_FORMAT, ALU, 2, true, 0 },
    { "j",     NULL, J_FORMAT, JUMP, NULL, false, 0 },
    { "lw",    NULL, I_FORMAT, LOAD, NULL, true, 2 },
    { "mfhi",  NULL, R_FORMAT, ALU, 1, true, 0 },
    { "mflo",  NULL, R_FORMAT, ALU, 1, true, 0 },
    { "mult",  NULL, R_FORMAT, ALU, 2, true, 0 },
    { "or",    NULL, R_FORMAT, ALU, 3, true, 0 },
    { "slt",   NULL, R_FORMAT, ALU, 3, true, 0 },
    { "sw",    NULL, I_FORMAT, STORE, NULL, true, 2},
    { "syscall", &syscall, R_FORMAT, OTHER, NULL, false, 0}
  };*/

struct registers{
  word registers[32];
  word programCounter;
  word hi, lo;
  // Comment these out
  // const int zero = 0; // zero register
  // long int a0, a1;    // argument registers
  // long int v0, v1;    // return registers
  // long int t0, t1, t2, t3, t4, t5, t6, t7; // temporary registers t1-t7
  /* long int s0, s1, s2, s3, s4, s5, s6, s7; // saved registers
  long int t8, t9;    // temporary registers t8 - t9
  long int k0, k1;    // kernel registers
  long int gp;        // global pointer register
  long int sp;        // stack pointer register
  long int fp;        // frame pointer register
  long int ra;        // return address register
  long int lo;        // lo register
  long int hi;        // hi register */
};

struct machineState {
  std::vector<word> code;
  std::vector<word> data;
  word codeBaseAddress;
  word dataBaseAddress;

  struct registers registerFile;
} machineState;

// Create an array for registers above
// of 32 ints, call it registers[32];
// Remaining is the mapping of the array;
// 

/*class mips_sim {
public:
private:
};

struct labels
{
  std::string label;
  int segmentOffset;
  int segmentNumber;
};*/

// int currentSegNo = 0;
// int currentSegOffset = 0;
// std::vector<instruct> instructions;
// std::vector<labels> list_of_labels;
// std::vector<registers> registerLine;

bool isValidOpCode(int opcode)
{
  for(int i=0;i < 17; i++)
  {
    if(opcode==validOpCodes[i].opcode)
      return true;
  }
  return false;
}

std::string getOpCode(int opcode)
{
  for(int i=0;i<17;i++)
  {
    if(validOpCodes[i].opcode==opcode)
      return validOpCodes[i].name;
  }
   char line [ 80];
  sprintf (line, "Unknown %d", opcode);
  return line;
}

std::string getOpCode(int opcode, int funct)
{
  for(int i=0;i<17;i++)
  {
    if(validOpCodes[i].opcode==0 && validOpCodes[i].funct==funct)
      return validOpCodes[i].name;
  }
  char line [ 80];
  sprintf (line, "Unknown %d %d", opcode, funct);
  return line;
}

std::string getRegName(int regNum)
{
  for(int i=0; i < 32; i++)
  {
    if(registerMap[i].address==regNum)
      return registerMap[i].name;
  }
   char line [ 80];
  sprintf (line, "Unknown %d", regNum);
  return line;
}

void printrtype (u instr)
{ 
if (instr.r.funct == 0x2a) {
std::cout << getOpCode(instr.r.opcode,instr.r.funct) << '\t';
std::cout << '$' << getRegName(instr.r.rd) << ',';
std::cout << '$' << getRegName(instr.r.rs) << ',';
std::cout << '$' << getRegName(instr.r.rt) << std::endl;
}
else if (instr.r.funct == 0xc) {
std::cout << getOpCode(instr.r.opcode,instr.r.funct) << std::endl;
}
else {
std::cout << getOpCode(instr.r.opcode,instr.r.funct) << '\t';
std::cout << '$' << getRegName(instr.r.rd) << ',';
std::cout << '$' << getRegName(instr.r.rs) << ',';
std::cout << '$' << getRegName(instr.r.rt) << std::endl;
}
}

void printitype (u instr)
{
switch (instr.i.opcode)
{
   case 2:
     std::cout << getOpCode(instr.i.opcode) << '\t';
     std::cout << instr.i.immed << std::endl;
     break;
   case 4:
   case 5:
   case 9:
     std::cout << getOpCode(instr.i.opcode) << '\t';
     std::cout << '$' << getRegName(instr.i.rt) << ',';  
     std::cout << '$' << getRegName(instr.i.rs) << ',';
     std::cout << instr.i.immed << std::endl;
   break;
   case 0x2b:
   case 0x23:
     std::cout << getOpCode(instr.i.opcode) << "\t\t";
     std::cout << '$' << getRegName(instr.i.rt) << ',';
     std::cout << instr.i.immed << "($";
     std::cout << getRegName(instr.i.rs) << ')' << std::endl; 
   break;
} 
}
bool gosyscall()
{
int num;
char line[MAXLINE]={0};
switch (machineState.registerFile.registers[2])
   {
   case 1:
     printf("%d\n", machineState.registerFile.registers[4]);
     break;
   case 5:
     fgets(line,MAXLINE,stdin);
     sscanf(line, "%1d", &num);
     machineState.registerFile.registers[2] = num;
     break;
   case 10:
     return false;
   }
 return true;
}

bool singleStep (bool dissemble, bool execute)
{
  // 1 Fetch instruction from PC 
  // using MachineState.PC vector
  // 
  word instruction = machineState.code[(machineState.registerFile.programCounter - machineState.codeBaseAddress) >> 2];

  // Print address of machineState.PC
  u instr;
  instr.d = instruction;
  int rs,rt,rd,immed;
  int pseudo_absolute;
  switch(instr.j.opcode)
    {
    case 0:
      printrtype(instr);
        if (!execute)   
         return false;
       switch (instr.r.funct) 
      {
        case 0xc:
          if (!gosyscall()) {
             return false; }
           break;
   //     case 0x10:
   //       if 
        case 0x1a:
          rt = instr.r.rt;
          rs = instr.r.rs;
          machineState.registerFile.lo = machineState.registerFile.registers[rs] / machineState.registerFile.registers[rt];
          machineState.registerFile.hi = machineState.registerFile.registers[rs] % machineState.registerFile.registers[rt];
          break;
        case 0x21:
          rt = instr.r.rt;
          rs = instr.r.rs;
          rd = instr.r.rd;
          machineState.registerFile.registers[rd] = machineState.registerFile.registers[rs] + machineState.registerFile.registers[rt];
          machineState.registerFile.programCounter += 4;
          break;
        case 0x24:
          rt = instr.r.rt;
          rs = instr.r.rs;
          rd = instr.r.rd;
          machineState.registerFile.registers[rd] = machineState.registerFile.registers[rs] & machineState.registerFile.registers[rt];
          machineState.registerFile.programCounter += 4;
          break;
        case 0x2a:
          rt = instr.r.rt;
          rs = instr.r.rs;
          rd = instr.r.rd;
          machineState.registerFile.registers[rd] = (machineState.registerFile.registers[rs] < machineState.registerFile.registers[rt]) ? 1 : 0;
          machineState.registerFile.programCounter += 4;
          break;
      }
      break;
    case 2:
      printitype(instr);
      pseudo_absolute = instr.j.pseudo_absolute;
      machineState.registerFile.programCounter += 4;
      break;
    case 4:
      printitype(instr);
        if (!execute)
         return false;

      rt = instr.i.rt;
      rs = instr.i.rs;
      immed = instr.i.immed;
      
      if (machineState.registerFile.registers[rt] == machineState.registerFile.registers[rs])
      machineState.registerFile.programCounter += immed;
      else 
      machineState.registerFile.programCounter += 4;
       break;
    case 5: 
      printitype(instr);
        if (!execute)
         return false;

      rt = instr.i.rt;
      rs = instr.i.rs;
      immed = instr.i.immed;

      if (machineState.registerFile.registers[rt] != machineState.registerFile.registers[rs])
      machineState.registerFile.programCounter += immed;
      else
      machineState.registerFile.programCounter += 4;
       break;
    case 9: 
      printitype(instr);
        if (!execute)
         return false;
      rt = instr.i.rt;
      rs = instr.i.rs;
      immed = instr.i.immed;
      machineState.registerFile.registers[rt] = machineState.registerFile.registers[rs] + immed;
      machineState.registerFile.programCounter += 4;
      break;  
    case 0x23:
    case 0x2b:
      printitype(instr);
        if (!execute)
         return false;
      rt = instr.i.rt;
      rs = instr.i.rs;
      immed = instr.i.immed;
      machineState.registerFile.registers[rt] = machineState.registerFile.registers[rs] + immed;
      machineState.registerFile.programCounter += 4;
    }
  return true;
}

void printMachineState ()
{
std::cout << "\nPC: " << machineState.registerFile.programCounter << std::endl;
std::cout << "inst: " << std::endl;;
static int l = 0;
  std::cout << "\nregs:\n";

  for (int i = 0; i < 32; i += 4)
  {
    for (int j = 0; j < 4; j++)
    {
      int k = i + j;
      std::cout << registerMap[k].name << " = \t" <<  machineState.registerFile.registers[k] << (j == 3 ? "\n" : "\t");
    }
  }
    std::cout << "$lo = \t" << machineState.registerFile.lo << "\t";
    std::cout << "$hi = \t" << machineState.registerFile.hi << "\n\n";

    std::cout << "data memory:" << std::endl;
    std::cout << "   data[  " << machineState.data[l++];
    std::cout << "] =    " << machineState.data[l] << "\n\n";
}

void run ()
{
// Initialize Machine State
machineState.codeBaseAddress = 0;
machineState.dataBaseAddress = 0x8000;
machineState.registerFile.programCounter = machineState.codeBaseAddress;

/*for (int i = 1; i < 32; i++) 
{
machineState.registerFile.registers[i] = -1;
}*/

int ctr=0;
machineState.registerFile.registers[28] = machineState.dataBaseAddress;

printMachineState();

while (singleStep(true,true))
 {
 printMachineState();
 } 
}

/*
long int executeInst (long int rd, long int rs, long int rt, long int immed)
{
// Can use while loop instead of for loop

registers r; 
  if (instructions[i].format == R_FORMAT)
  {
    switch(instructions[i].type) 
    {
      case ALU:
        {
          rd = rs + rt; // addu, will elaborate
          return rd;
        }
    }
  }
  if (instructions[i].format == I_FORMAT)
  {
    switch(instructions[i].type)
    {
      case ALU:
        {
          rt = rs + immed;
          return rt;
        }
case 
    }
  }

registerLine.pushback(r);
  }*/

/* void printAllInstructions()
{
  for (int i = 0; i < instructions.size(); ++i)
  {
    std::cout << "[" << i << "]:\t" << printInstLine(i);
  }
}*/

/* void printtoTxt (long int rd, long int rs, long int rt)
{
  std::cout << "PC:  " << segmentNo << std::endl;

  // Recall function 
  for (int i = 0; i < instructions.size(); ++i) 
  {
    std::cout << "inst: " << printInstLine(i);  

    std::cout << "regs:\n";

    std::cout << "$at = \t" << registerLine[i].at << "\t";
    std::cout << "$v0 = \t" << registerLine[i].v0 << "\t";
    std::cout << "$v1 = \t" << registerLine[i].v1 << "\n";

    std::cout << "$a0 = \t" << registerLine[i].a0 << "\t";
    std::cout << "$a1 = \t" << registerLine[i].a1 << "\t";
    std::cout << "$a2 = \t" << registerLine[i].a2 << "\t";
    std::cout << "$a3 = \t" << registerLine[i].a3 << "\n";   

    std::cout << "$t0 = \t" << registerLine[i].t0 << "\t";
    std::cout << "$t1 = \t" << registerLine[i].t1 << "\t";
    std::cout << "$t2 = \t" << registerLine[i].t2 << "\t";
    std::cout << "$t2 = \t" << registerLine[i].t2 << "\t";
    std::cout << "$t3 = \t" << registerLine[i].t3 << "\n";

    std::cout << "$t4 = \t" << registerLine[i].t4 << "\t";
    std::cout << "$t5 = \t" << registerLine[i].t5 << "\t";
    std::cout << "$t6 = \t" << registerLine[i].t6 << "\t";
    std::cout << "$t7 = \t" << registerLine[i].t7 << "\n";

    std::cout << "$s0 = \t" << registerLine[i].s0 << "\t";
    std::cout << "$s1 = \t" << registerLine[i].s1 << "\t";
    std::cout << "$s2 = \t" << registerLine[i].s2 << "\t";
    std::cout << "$s3 = \t" << registerLine[i].s3 << "\n";

    std::cout << "$s4 = \t" << registerLine[i].s4 << "\t";
    std::cout << "$s5 = \t" << registerLine[i].s5 << "\t";
    std::cout << "$s6 = \t" << registerLine[i].s6 << "\t";
    std::cout << "$s7 = \t" << registerLine[i].s7 << "\n";

    std::cout << "$t8 = \t" << registerLine[i].t8 << "\t";
    std::cout << "$t9 = \t" << registerLine[i].t9 << "\t";
    std::cout << "$k0 = \t" << registerLine[i].k0 << "\t";
    std::cout << "$k1 = \t" << registerLine[i].k1 << "\n";

    std::cout << "$gp = \t" << registerLine[i].gp << "\t";
    std::cout << "$sp = \t" << registerLine[i].sp << "\t";
    std::cout << "$fp = \t" << registerLine[i].fp << "\t";
    std::cout << "$ra = \t" << registerLine[i].ra << "\n";

    std::cout << "$lo = \t" << registerLine[i].lo << "\t";
    std::cout << "$hi = \t" << registerLine[i].hi << "\n";

    std::cout << "data memory:\n";
    std::cout << "   data[ 0 ] =\t" << registerLine[i].data;
  }

  // When loop finished, print final summary below:
} 
*/

void readObject (char * filename)
{
  FILE * objfile = fopen(filename, "r");
  
  if (objfile == NULL) {
    printf("Could not find file.\n");
    exit(1);
    }
  char line[MAXLINE]={0};
  fgets(line,MAXLINE,objfile);
 //  printf("%s\n", line);
  int instruction_count;
  int data_count;
  sscanf(line, "%d %d", &instruction_count, &data_count);
  printf("Read object: %d %d\n", instruction_count, data_count);

  for (int i = 0; i < instruction_count; i++)
  {
    word instruction;

    fgets(line,MAXLINE,objfile);
    sscanf(line, "%x", &instruction);
    machineState.code.push_back(instruction); 
  } 


  for (int i = 0; i < data_count; i++)
  {
    word instruction;

    fgets(line,MAXLINE,objfile);
    sscanf(line, "%x", &instruction);
    machineState.data.push_back(instruction);
  }
  // Have a separate function that can handle either
  // and call it twice in this function.
  // First call would be to instruction_count and a reference to code vector
  // Second call would be to data_count and a reference to code vector.
}

int main (int argc, char ** argv)
{
  long int num;
  char line[MAXLINE]={0};
  int inst_count = 0; 
  int finalCount = 0; // final Instruction Count
  int format;
  // instruct a;
  // labels l;

  if (argc != 2) {
  printf("Usage error: 1 parameter expected \n");
  return 1;
  }
  readObject(argv[1]);

  std::cout << "insts:\n";
  for (int i = 0; i < machineState.code.size(); i++)
       {
       machineState.registerFile.programCounter = i * 4;
       printf("%4d: ", i);
       singleStep(true,false);
       } 

  std::cout << "\ndata:\n";
  for (int i = 0; i < machineState.data.size(); i++)
       {
        printf("%3lu:", i + machineState.code.size());
        std::cout << machineState.data[i] << "\n";
       }

  run();
  
  // If argc != 1, fprintf error message
  
 /* while (fgets(line,MAXLINE,stdin)) {
  scanf("%lx", &u.d);


  if(isValidOpCode(a.opcode))
  {
    inst_count+=1;
    currentSegOffset += 4;
  } */

  /*  else if(a.opcode == ".data")
  {
    finalCount = inst_count;
    inst_count = 0x00020000;
    currentSegNo = 1;
    currentSegOffset = 0;
  }
  */ // NEED TO FIND OUT WHAT ".data" TRANSLATE TO IN BINARY / HEX  ^^^^^^^^

  /* if (u.r.opcode == 0) {
    // printf("This is an R Instruction.\n");
    // printf("You entered: opcode:%u rd:%u rs:%u rt:%u shamt:%u funct:%u \n", u.r.opcode, u.r.rd, u.r.rs, u.r.rt, u.r.shamt, u.r.funct);
    a.opcode = u.r.opcode;
    a.rd = u.r.rd;
    a.rs = u.r.rs;
    a.rt = u.r.rt;
    a.shamt = u.r.shamt;
    a.funct = u.r.funct;
    a.format = R_FORMAT;
    a.type = ALU; // MUST elaborate in future      
  }
  else {
    if (u.j.opcode == 2) {
      // printf("This is a J Instruction.\n");
      // printf("You entered: opcode:%u pseudo_absolute:%u \n", u.j.opcode, u.j.pseudo_absolute);
      a.opcode = u.j.opcode;
      l.segmentNumber = u.j.pseudo_absolute;
      a.format = J_FORMAT;
      a.type = JUMP;
    }
    else {
      //      printf("This is an I instruction.\n");
      // printf("You entered: opcode:%u rs:%u rt:%u immed:%ld \n", u.i.opcode, u.i.rs, u.i.rt, u.i.immed);
      a.opcode = u.i.opcode;
      a.rs = u.i.rs;
      a.rt = u.i.rt;
      a.immed = u.i.immed;
      a.immed = (a.immed << 48) >> 48; 
      a.format = I_FORMAT;
      switch (a.opcode)
      {
        case 4:
        case 5:
          {
            a.type = BRANCH;
          }
        case 9:
          {
            a.type = ALU;
            break;
          }
        case 35:
          {
            // Create a bool check here: is immed field an int or does it match
            // a label's address? If match, it's a label.
            a.type = LOAD;
            break;
          }
        case 43:
          {
            a.type = STORE;
            break;
          }
        default:
          {
            a.type = TYPE_NA;
          }
      } 

      //printf("This is an I instruction.\n");
      //printf("You entered: opcode:%u rs:%u rt:%u immed:%ld \n", u.i.opcode, u.i.rs, u.i.rt, u.i.immed);
      //printf("You entered: opcode:%u rs:%u rt:%u immed:%ld \n", a.opcode, a.rs, a.rt, a.immed);
    } 
   }
  instructions.push_back(a);
  } // end fgets(...) 
  */
  return 0;
}
 

  // loop until instructions.size();
  // Step 1: Decode from into hex into instruction
  // Function Name: Print
 /* void printInstLine (int i) {
  // for (i = 0; i < instructions.size(); ++i) 
  // {
    if (instructions[i].format == R_FORMAT) {
      switch(instructions[i].funct) {
      case 12: {
        std::cout << "[" << i << "]: "; 
        std::cout << "syscall" << std::endl;
        break;
      }
      default: {
        std::cout << "[" << i << "]: "; 
        std::cout << getOpCode(instructions[i].funct) << "\t" << 
        "$" << getInst(instructions[i].rd) << 
        ",$" << getInst(instructions[i].rs) << 
        ",$" << getInst(instructions[i].rt) << std::endl;
       } // end default
      } // end switch
    } // end isR
    if (instructions[i].format == I_FORMAT) {
      switch(instructions[i].opcode) {
        case 4: 
        case 5: {
        // bne / beq procedure:
        // Step 1: Decode registers and opcode
        // Step 2: Read offset #
        // Step 3: Write offset # into label vector
        // Step 4: Perhaps maybe initialize MIPS instruction class variable
        // isBranch = true, so that we always know this is beq or bne.
          std::cout << "[" << i << "]: " << getOpCode(instructions[i].opcode) << "\t" <<
            "$" << getInst(instructions[i].rs) <<
            ",$" << getInst(instructions[i].rt) <<
            "," << instructions[i].immed << std::endl;
          break;
        } 
        case 35:
        case 43: {
        // lw / sw procedure:
        // Step 1: Decode registers and opcode
        // Step 2: Read base segment number: is most likely register $gp
        // Step 3: If-Else Check: If opcode is sw:
        // Then write and save base segment + offset to register rt
        // Then save value that's inside base segment + offset to register rt
        // Remember: lw $t,C($s)      # $t = Memory[$s + C]
        //           sw $t,C($s)      # Memory[$s + C] = $t   
        // lw loads VALUE inside of an array to register rt
        // sw stores memory ADDRESS of an array to register rt (see Stack
        // Overflow bookmark)
        // Step 4: 2nd If-Else Check: If immediate field is an int or a label:
        // If is int: add base segment number (rs) with immediate.
        // If is label: call getLabelAddress(Label) and sum it with base segment
        // number (rs).
        // Step 5 (PROB is Step 3): We're dealing with ints, but we must be sure.
        // To get exact offset number, divide offset number by sizeof(int) or
        // sizeof(datatype).
        std::cout << "[" << i << "]: " << getOpCode(instructions[i].opcode) << "\t\t" <<
          "$" << getInst(instructions[i].rt) <<
          "," << instructions[i].immed <<
          "($" << getInst(instructions[i].rs) << 
          ")" << 
          std::endl;
        break;
        } 
        default: {
        // addiu procedure, common case:
          //        std::cout << "This is an addiu:\n";
        std::cout << "[" << i << "]: " << getOpCode(instructions[i].opcode) << "\t" <<
          "$" << getInst(instructions[i].rt) <<
          ",$" << getInst(instructions[i].rs) <<
          "," << instructions[i].immed << std::endl;
        }
      }
    } // end isI
  // } // end for
} */
