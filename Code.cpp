#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
/************************************************************
* 1. -------ARRAY INDEX------
 ********************************************************/
/*************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ****************************************/
void arrayVulnerability(int i)
{
    int buffer[4];
    bool access = false;
    bool * ptr = &access;
    buffer[i] = -1;
    cout << "Access should be 0: " << access << endl;
}
/**************************************
 * ARRAY WORKING
 * Call arrayVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void arrayWorking()
{
    cout << "Working Function: " << endl;
    int working = 1;
    arrayVulnerability(working);
}
/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker
 *************************************/
void arrayExploit()
{
    cout << "Exploit Function: " << endl;
    int exploit = -1;
    arrayVulnerability(exploit);
}

/*****************************************************
* 2. -----------POINTER SUBTERFUGE----------
 *******************************************************/
/****************************************
 * Pointer Subterfuge Vulnerability
 * 1. There must be a pointer used in the code.
 * 2. There must be a way to overwrite the pointer
 * 3. After the pointer is overwritten, the pointer is dereferenced
 ****************************************/
void psVulnerability(long * array, int size) {
  long buffer[2];
  char message[100] = "Safe";
  for (int i = 0; i < size; i++) {
    buffer[i] = array[i];
  }
  cout << "Message is: \"" << message << "\".\n";
}
/*************************************
 * Pointer Subterfuge WORKING
 * Call psVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void psWorking() {
  long array[2] = {1, 1};
  psVulnerability(array, 1);
}
/****************************************
 * Pointer Subterfuge Exploitation
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the pointer
 * 2. The attacker must be able to provide a new pointer
 *    referring to data altering the normal flow of the program
 ****************************************/
void psExploit() {
    long array[3] = {1, 1, (long)"Dangerous"};
    psVulnerability(array, 3);
}
/********************************************************************
* 3. ---------ARC Injection--------------------------------------
 ***********************************************************************/
/*********************************
 * ARC VULNERABILITY
 * 1. There must be a function pointer used in the code.
 * 2. Through some vulnerability, there must be a way for user input
 *    to overwrite the function pointer. This typically happens through
 *    a stack buffer vulnerability.
 * 3. After the memory is overwritten, the function pointer must
 *    be dereferenced
 ********************************/
void arcVulnerability(int size, long * array) {
  long buffer[2];
    void (* pointer_function)() = psWorking;
  for (int i = 0; i < size; i++) {
      buffer[i] = array[i];
  }
  cout << "ARC Velnerability is: \"";
  pointer_function();
}
/*************************************
 * ARC WORKING
 * Call intVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void arcWorking() {
    long array[2] = {1, 1};
    arcVulnerability(1, array);
}
/*********************************
 * ARC EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the function pointer
 * 2. The attacker must have the address to another function
 *    which is to be used to replace the existing function pointer
  ********************************/
void arcExploit() {
  long array[3] = {1, 1, (long)psExploit};
  arcVulnerability(3, array);
}
 /**********************************************************
* 4. -----------------VTable Spraying--------------------
 ************************************************************************/
/***********************************
 * VULNERABILITY
 * 1. The vulnerable class must be polymorphic.
 * 2. The class must have a buffer as a member variable.
 * 3. Through some vulnerability, there must be a way for user input
 *    to overwrite parts of the VTable.
 * 4. After a virtual function pointer is overwritten,
 *    the virtual function must be called.
 **********************************/
void Vulnerability () {
}
/*************************************
 * VTable WORKING
 * Call Vulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void vtableWorking() {
}
/************************************
 * VTABLE EXPLOIT
 * 1. Through some vulnerability, the VTable pointer
 *     or a function pointer within the VTable must be overwritten
 * 2. The attacker must have the address to another VTable pointer
 *     or a function pointer
 ***********************************/
void vtableExploit() {
 }
 /***********************************************************
* 5. -------------------Stack Smashing------------------------
 ***********************************************************************/
/***********************************************
 * STACK VULNERABILITY
 * 1. There must be a buffer on the stack
 * 2. the buffer must be reachable from an external input
 * 3. The mechanism to fill the buffer must not check the correct buffersize
 **********************************************/
void stackVulnerability(long c) {
  long integer[32];
  cout << "Ingeters: ";
  for (int i = 0; i < c; i++) {
    integer[i] = c;
  }
  cout << *integer << endl;
}
/*************************************
 * Stack Smashing WORKING
 * Call stackVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void stackWorking() {
    long working = 1;
    cout << "The Stack Smashing is None-Malicious" << endl;
    stackVulnerability(working);
}
/*********************************************
 * STACK EXPLOIT
 * 1. The attacker must provide more data into the
 *    outwardly facing buffer than the buffer is designed to hold
 * 2. The attacker must know where the the stack pointer resides
 *    on the stack. This should be just beyond the end of the buffer
 * 3. The attacker must insert machine language instructions in the buffer.
 *    This may occur before, after, or even around the stack pointer. The
 *    machine language could be already compiled code in the program
 * 4. The attacker must overwrite the stack pointer. The old value,
 *    directing the flow of the program after the function is returned,
 *    must be changed from the calling function to the provided
 *    machine language in step 3.
 *********************************************/
void stackExploit() {
    long exploit = 9876543213;
    cout << "The Stack Smashing is Malicious" << endl;
    stackVulnerability(exploit);
}
 /********************************************************
* 6. -----------------Heap Spraying----------------
 ****************************************/
/*************************************
 * HEAP VULNERABILITY
 * 1. There must be two adjacent heap buffers.
 * 2. The first buffer must be reachable through external input.
 * 3. The mechanism to fill the buffer from the external input must
 *    not correctly check for the buffer size.
 * 4. The second buffer must be released before the first.
 *************************************/
void heapVulnerability(char *input, int d) {
    char * bufferOne = new char[4];
    char * bufferTwo = new char[4];
    // The first buffer must be reachable through external input.
    assert(bufferOne < bufferTwo);
    for (int i = 0; i < d; i++) {
      bufferOne[i] = input[i];
    }
    delete [] bufferTwo; // free second buffer before the first one
    delete [] bufferOne;
    cout << "The Heap Velnerability is good" << endl;
}
/*************************************
 * Heap Spraying WORKING
 * Call heapVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void heapWorking() {
    char input[4] = "Hi";
    int working_size = 4;
    heapVulnerability(input, working_size);
}
/*************************************
 * HEAP EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing
 *    heap buffer than the buffer is designed to hold
 * 2. The attacker must know the layout of the Memory Control Block (MCB)
 *    (essentially a linked list) residing just after the buffer
 * 3. The attacker must provide a new MCB containing both the location
 *    of the memory overwrite and the new data to be overwritten
 ***********************************/
void heapExploit() {
  int size = 128;
    char input[128] = "This is Computer Security Class in Winter 2021.";
  heapVulnerability(input, size);
}
 /******************************************************
* 7. ---------------Integer Overflow-------------------
 ********************************************************/
/********************************************
 * INTEGER VULNERABILITY
 * 1. There must be a security check represented by an expression.
 * 2. The expression must have the potential for overflow.
 * 3. At least one of the numbers used to compute the sentinel
 *    must be reachable through external input.
 *********************************************/
void intVulnerability(int offset) {
  int buffer[256];     // buffer
  int *sentinel = buffer + 256; // end of buffer
  // cout << offset << endl;
  //cin >> offset;
  cout << endl << "Integer Vulnerability: ";
  if (offset + buffer < sentinel) {
    //cin >> buffer[offset];
    cout << "Working " << offset << " IV is Sucessfully Accessed!" << endl;
  } else {
    cout << "Exploiting " << offset << " IV is Unsucessfully Accesed.." << endl;
  }
}
/*************************************
 * INTEGER WORKING
 * Call intVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void intWorking() {
  long working = 100;
  intVulnerability(working);
}
/**********************************************
 * INTEGER EXPLOIT
 * 1. Provide input, either a buffer size or a single value,
 *    that is directly or indirectly used in the vulnerable expression
 * 2. The input must exceed the valid bounds of the data-type,
 *    resulting in an overflow or underflow condition
 **********************************************/
void intExploit() {
  long exploit = 6745;
  intVulnerability(exploit);
}
/*********************************************************
* 8. -------------ANSI-Unicode Conversion------------------
 ******************************************************************/
/*********************************************************
 * ANSI - UNICODE VULNERABILITY
 * 1. There must be a buffer where the basetype is greater than one.
 * 2. Validation of the buffer must check the size of the buffer
 *    rather than the number of elements in the buffer.
 ********************************************************/
void ansiVulnerability(int number) {
  long unicodeText[number];
}
/**************************************
 * ANSI WORKING
 * Call ansiVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void ansiWorking() {
}
/***********************************************
 * ASCI - UNICODE EXPLOIT
 * 1. The attacker must provide more than half as much data
 *    into the outwardly facing buffer as it is designed to hold
 * 2. From here, a variety of injection attacks are possible. The most likely candidates are stack smashing or heap smashing. In the above *  example, the third parameter of the copyUnicodeText() function is the number of elements in the string (256 elements), not the size of * the string (512 bytes). The end result is a buffer overrun of 256 bytes.
 **********************************************/
void ansiExploit() {
}
/*************************************
* Main Function will call all functions
 ****************************************/
int main() {
  cout << "1. Array Index" << endl;
  cout << "2. Pointer subterfuge" << endl;
  cout << "3. ARC Injection" << endl;
  cout << "4. VTable Spraying" << endl;
  cout << "5. Stack Smashing" << endl;
  cout << "6. Heap Spraying" << endl;
  cout << "7. Integer Overflow" << endl;
  cout << "8. ANSI-Unicode Conversion" << endl;

  int choose; // Variable for selecting vulnerability
  cout << "Which vulnerability do you want to explore? Select your number:";
  cin >> choose;
  switch (choose) {
    case 1:
      arrayWorking();
      arrayExploit();
      break;
    case 2:
      psWorking();
      psExploit();
      break;
    case 3:
      arcWorking();
      arcExploit();
      break;
    case 4:
      vtableWorking();
      vtableExploit();
      break;
    case 5:
      stackWorking();
      stackExploit();
      break;
    case 6:
      heapWorking();
      heapExploit();
      break;
    case 7:
      intWorking();
      intExploit();
      break;
    case 8:
      ansiWorking();
      ansiExploit();
      break;
    default:
      cout << "Not part of any working options. You can run the program again." << endl;
  }
  return 0;
}
