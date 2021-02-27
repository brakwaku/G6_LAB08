/**********************************************
 * Lab 07: Group 06
 * Authors: Charles Rich, Kwaku Appau-Nkansah,
 *  Jacob Muhlestein, Doug Barlow, Chad Smith,
 *  and Ryan Budd
 * Instructor: Brother Wilson
 **********************************************/
#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

void safe() { cout << "safe\n"; }
void unsafe() { cout << "unsafe\n"; }

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
void psVulnerability(bool exploit) {
    long * buffer[1];
    char * p1 = "Safe";
    char * p2 = "Unsafe";

    if (exploit == true) {
        buffer[1] = reinterpret_cast<long*>((void*&)p2);
    }

    cout << "Message is: \"" << p1 << "\".\n";
}

/*************************************
 * Pointer Subterfuge WORKING
 * Call psVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void psWorking() {
  cout << "Working Function:" << endl;
  bool exploit = false;
  psVulnerability(exploit);
}

/****************************************
 * Pointer Subterfuge Exploitation
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the pointer
 * 2. The attacker must be able to provide a new pointer
 *    referring to data altering the normal flow of the program
 ****************************************/
void psExploit() {
    cout << "Exploit Function:" << endl;
    bool exploit = true;
    psVulnerability(exploit);
}

/********************************************************************
* 3. ---------ARC INJECTION--------------------------------------
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
void arcVulnerability(long * input) {
    long * buffer[1];
    void (* pointerFunction)() = safe;

    buffer[1] = input;

    cout << "The pointer function is ";
    pointerFunction();
}

/*************************************
 * ARC WORKING
 * Call intVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void arcWorking() {
    cout << "Working Function:" << endl;
    long * working = reinterpret_cast<long*>((void*)safe);
    arcVulnerability(working);
}

/*********************************
 * ARC EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the function pointer
 * 2. The attacker must have the address to another function
 *    which is to be used to replace the existing function pointer
  ********************************/
void arcExploit() {
    cout << "Exploit Function:" << endl;
    long * exploit = reinterpret_cast<long*>((void*)unsafe);
    arcVulnerability(exploit);
}

 /**********************************************************
* 4. -----------------VTABLE SPRAYING--------------------
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
 * 5. -------------------STACK SMASHING------------------------
 ***********************************************************************/
/***********************************************
 * STACK VULNERABILITY
 * 1. There must be a buffer on the stack
 * 2. the buffer must be reachable from an external input
 * 3. The mechanism to fill the buffer must not check the correct buffersize
 **********************************************/
void dangerous() {
  cout << "Stack Smashed!!!" << endl;
}

void stackVulnerability(char * input) {
    char text[2];
    int i = 0;

    for (char * p = input; *p; ++p, ++i) {
        text[i] = *p;
    }
}

/*************************************
 * Stack Smashing WORKING
 * Call stackVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void stackWorking() {
    cout << "Working Function:" << endl;
    char working[2] = "!";
    stackVulnerability(working);
    cout << "Finished" << endl;
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
    cout << "Exploit Function:" << endl;

    char exploit[15] = "AA ìHåHU";
    stackVulnerability(exploit);
    cout << "Finished" << endl;
}

 /********************************************************
* 6. -----------------HEAP SPRAYING----------------
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
    cout << "The Heap did not crash." << endl;
}

/*************************************
 * Heap Spraying WORKING
 * Call heapVulnerability() in a way that does
 * not yield unexpected behavior
 ***********************************/
void heapWorking() {
    cout << "Working Function:" << endl;
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
  cout << "Exploit Function:" << endl;
  int size = 128;
  char input[128] = "This is Computer Security Class in Winter 2021.";
  heapVulnerability(input, size);
}

 /******************************************************
* 7. ---------------IINTEGER OVERFLOW-------------------
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

  cout << "Integer Vulnerability: ";
  if (offset + buffer < sentinel) {
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
  cout << "Working function:" << endl;
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
  cout << "Exploit function:" << endl;
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
void ansiVulnerability(char text[], int size) {
    cout << "Reading String: ";
    for (int i = 0; i < size - 1; i++) {
            cout<< text[i];
    }
    cout << endl << endl;
}
/**************************************
 * ANSI WORKING
 * Call ansiVulnerability() in a way that does
 * not yield unexpected behavior
 *************************************/
void ansiWorking() {
    cout << "Working Function: \n"
         << "Passing ANSI string: 123 \n";
    char ansi[] = "123";
    ansiVulnerability (ansi, sizeof(ansi));
}
/***********************************************
 * ASCI - UNICODE EXPLOIT
 * 1. The attacker must provide more than half as much data
 *    into the outwardly facing buffer as it is designed to hold
 * 2. From here, a variety of injection attacks are possible.
 *    The most likely candidates are stack smashing or heap smashing.
 **********************************************/
void ansiExploit() {
    cout << "Exploit Function: \n"
         << "Passing UNICODE string: 123 \n";
    short uni[] = {1,2,3};
    char *convert = (char*)uni;
    ansiVulnerability (convert, sizeof(uni));
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
  cout << "Which vulnerability do you want to explore? Select your number: ";
  cin >> choose;
  switch (choose) {
    case 1:
      cout << endl;
      arrayWorking();
      cout << endl;
      arrayExploit();
      break;
    case 2:
      cout << endl;
      psWorking();
      cout << endl;
      psExploit();
      break;
    case 3:
      cout << endl;
      arcWorking();
      cout << endl;
      arcExploit();
      break;
    case 4:
      vtableWorking();
      vtableExploit();
      break;
    case 5:
      cout << endl;
      stackWorking();
      cout << endl;
      stackExploit();
      break;
    case 6:
      cout << endl;
      heapWorking();
      cout << endl;
      heapExploit();
      break;
    case 7:
      cout << endl;
      intWorking();
      cout << endl;
      intExploit();
      break;
    case 8:
      cout << endl;
      ansiWorking();
      ansiExploit();
      break;
    default:
      cout << "Not part of any working options. You can run the program again." << endl;
  }
  return 0;
}
