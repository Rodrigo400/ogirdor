
//Author / Modified by : Cesar Loya
// Date June 24, 2017
//cmps3350 - Source code

//*******************************************************************
//Progress
//June 24 - Mariachi appears on screen
//June 24 - general Enemy class ready
//June 24 - Mari class inherited from Enemy
//June 24 - OOP foundation ready

//*******************************************************************
//Responsabilities
//code object oriented Enemies
//proper animation
//walk in inervals
//animation for death 
//Enemies may have unique traits

//Week 4 goal - OO foundation and display one enemy

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
//#include "log.h"
#include "ppm.h"
#include "fonts.h"
#include "game.h"
using namespace std;

//global variables
int m_position = -500;
int ss_position = -1500;

// this array will store the positions of enemies
const int size = 4; // 0-9
int array[size]= {200,300,800,1200};
int start = 0;



class my_time {
    public:
	double physicsRate;
	double oobillion;
	struct timespec timeStart, timeEnd, timeCurrent;
	struct timespec walkTime;
	my_time() {
	    physicsRate = 1.0 / 30.0;
	    oobillion = 1.0 / 1e9;
	}
	double timeDiff(struct timespec *start, struct timespec *end) {
	    return (double)(end->tv_sec - start->tv_sec ) +
		(double)(end->tv_nsec - start->tv_nsec) * oobillion;
	}
	void timeCopy(struct timespec *dest, struct timespec *source) {
	    memcpy(dest, source, sizeof(struct timespec));
	}
	void recordTime(struct timespec *t) {
	    clock_gettime(CLOCK_REALTIME, t);
	}

} tim;




void mari_physics(void)
{
    tim.recordTime(&tim.timeCurrent);
    double timeSpan = tim.timeDiff(&tim.walkTime, &tim.timeCurrent);
    if (timeSpan > gl.m_delay) {
	m_position++;
	gl.m_walkFrame++;
	if (gl.m_walkFrame >= 7){
	    gl.m_walkFrame -= 7;
	    m_position--;
	}
	tim.recordTime(&tim.walkTime);
    }

}

//figure out proper physics for the shooting star
void shooting_star_physics(void)
{
    tim.recordTime(&tim.timeCurrent);
    double timeSpan = tim.timeDiff(&tim.walkTime, &tim.timeCurrent);
    if (timeSpan > gl.ss_delay) {
	ss_position++;
	gl.ss_walkFrame++;
	if (gl.ss_walkFrame >= 64){
	    gl.ss_walkFrame -= 64;
	    ss_position=ss_position-2;
	}
	tim.recordTime(&tim.walkTime);
    }
}


// make tacos, shoot tacos
void make_tacos()
{
    //gl.taco[gl.taco_count].cx =  y ; // find bug
    gl.taco[gl.taco_count].cx =        obama.cx;
    gl.taco[gl.taco_count].cy =        obama.cy;
    gl.taco[gl.taco_count].velocity =  gl.ob_particle_velocity;
    gl.taco[gl.taco_count].direction = gl.facing;
    gl.taco_count++;
}


void shoot_tacos()
{
    if(gl.isPressed == true){
	printf("TACOS GOOOOOO");
	make_tacos();
	gl.isPressed = false;
    }
}




Ppmimage* mari_image() 
{
    system("convert ./images/Enemy_Mariachi_3.gif ./images/Enemy_Mariachi_3.ppm");
    return ppm6GetImage("./images/Enemy_Mariachi_3.ppm");
}


Ppmimage* female_image() 
{
    system("convert ./images/female_fighter.png ./images/female_fighter.ppm");
    return ppm6GetImage("./images/female_fighter.ppm");
}


Ppmimage* obama_image()
{
    system("convert ./images/obama.gif ./images/obama.ppm");
    return ppm6GetImage("./images/obama.ppm");
}


Ppmimage* obama_image2()
{
    system("convert ./images/obama.gif ./images/obama.ppm");
    return ppm6GetImage("./images/obama.ppm");
}


Ppmimage* obama_image3()
{
    system("convert ./images/obama.gif ./images/obama.ppm");
    return ppm6GetImage("./images/obama.ppm");
}



Ppmimage* sun_image()
{
    system("convert ./images/sun.gif ./images/sun.ppm");
    return ppm6GetImage("./images/sun.ppm");
}

Ppmimage* shooting_star_image()
{
    system("convert ./images/shooting_star.jpg ./images/shooting_star.ppm");
    return ppm6GetImage("./images/shooting_star.ppm");
}


/*
 * void combat{
 if(mariachi.position == mainCharacter.position){
//inflict damage on mainCharacter.health 

}
}
*/


//first enemy
void show_mari() 
{
    int y = 165;
    //mariEnemy.cy = 175; // y cord
    float ht = 100.0;//height of mari
    float w = ht*0.5; 

    int temp = 1000;

    //make variables for borders

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mari_Texture); 
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = gl.m_walkFrame % 7;  //animation  
    int ay = 0;

    //takes care of animation
    if (gl.m_walkFrame >= 7){
	//if animation reaches LAST sprite
	//start from start again
	ay = 1;
    }
    float tx = (float)ax / 7.0;
    float ty = (float)ay / 1.0;


    cout << "before loop: " << m_position << endl; 
    cout << "position: " << m_position << endl;

    if(m_position < -600){  //was 600
	//walks to the left 
	m_position++;
	cout << "position: " << m_position << endl;
	glBegin(GL_QUADS);
	glTexCoord2f(tx,      ty+.6); glVertex2i(mariEnemy.cx+ m_position+ temp +w, y-ht);
	glTexCoord2f(tx,      ty+0);    glVertex2i(mariEnemy.cx+ m_position+ temp +w, y+ht);
	glTexCoord2f(tx+.14, ty+0);    glVertex2i(mariEnemy.cx +m_position+ temp -w, y+ht);
	glTexCoord2f(tx+.14, ty+.6); glVertex2i(mariEnemy.cx + m_position+ temp -w, y-ht);

	//hopefully
	//(mainChar.cx >= mariEnemy.cx+m_position+temp+w? mainChar.health--: m_position++);
	if(mainChar.cx >= mariEnemy.cx+m_position+temp-w &&
		mainChar.cx <= mariEnemy.cx+m_position+temp+w){
	    if(mainChar.cy <= y-ht || mainChar.cy >= y+ht || mainChar.cy == y+ht || mainChar.cy == y-ht){
		mainChar.health=30; //mainChar.health;	
	    }else{
		//mainChar.health-=.20;
	    }
	}

	//if pos > -602,set pos to -500,else pos++	
	(m_position > -602? m_position=-500: m_position++);




    }


    cout << "position: " << m_position << endl;


    if(m_position > -600) { //was 600
	// walk right
	m_position--;
	cout << "position: " << m_position << endl;
	glBegin(GL_QUADS);
	glTexCoord2f(tx,      ty+.6);  glVertex2i(mariEnemy.cx+ m_position+ temp +w, y-ht);
	glTexCoord2f(tx,      ty+0);   glVertex2i(mariEnemy.cx+m_position+temp+w, y+ht);
	glTexCoord2f(tx-.14, ty+0);    glVertex2i(mariEnemy.cx +m_position+temp -w, y+ht);
	glTexCoord2f(tx-.14, ty+.6);   glVertex2i(mariEnemy.cx + m_position+temp -w, y-ht);

	//(mainChar.cx >= mariEnemy.cx+m_position+temp-w? mainChar.health--: m_position--);


	if(mainChar.cx >= mariEnemy.cx+m_position+temp-w &&
		mainChar.cx <= mariEnemy.cx+m_position+temp+w){
	    if(mainChar.cy <= y-ht || mainChar.cy >= y+ht || mainChar.cy == y+ht || mainChar.cy == y-ht){
		mainChar.health=30;  //health;
	    }else{
		//mainChar.health-=.20;
	    }
	}

	(m_position < -599?m_position=-700:m_position--);

    }


    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);


    //WORK ON TIME library to sort enemies every 3 seconds

}                                                                               

void show_female() 
{
    if (gl.initDone == 0) {
	float x = gl.xres/1; 
	x = x-60; //x cord
    }
    female.cy = 110; // y cord
    float ht = 50.0;//estatura de la mujer
    float w = ht*0.5; 

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.female_Texture); 
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;   
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 8.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    //image starts at 12.5 , since 8 x 8
    glTexCoord2f(tx,      ty+ .12); glVertex2i(female.cx +w, female.cy-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(female.cx +w, female.cy+ht);
    glTexCoord2f(tx+.08, ty);    glVertex2i(female.cx-w, female.cy+ht);
    glTexCoord2f(tx+.08, ty+.12); glVertex2i(female.cx-w, female.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void show_obama()
{
    /* if (gl.initDone == 0) {
       float x = gl.xres/1;
       x = x-60; //x cord
       }*/
    //obama.cx = 200;   charceter.cx is to make him follow megaman
    obama.cy = 300; // y cord
    float ht = 75.0;//height of mari
    float w = ht*0.5;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.obama_Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 7.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+1.0); glVertex2i(obama.cx+w, obama.cy-ht);
    glTexCoord2f(tx,      ty+0);    glVertex2i(obama.cx+w, obama.cy+ht);
    glTexCoord2f(tx+1.0, ty+0);    glVertex2i(obama.cx-w, obama.cy+ht);
    glTexCoord2f(tx+1.0, ty+1.0); glVertex2i(obama.cx-w, obama.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

/*
   void show_obama2()
   {
   if (gl.initDone == 0) {
   float x = gl.xres/1;
   x = x-60; //x cord
   }
//obama.cx = 200;   charceter.cx is to make him follow megaman
obama.cy = 300; // y cord
float ht = 75.0;//height of mari
float w = ht*0.5;

glPushMatrix();
glColor3f(1.0, 1.0, 1.0);
glBindTexture(GL_TEXTURE_2D, gl.obama_Texture2);
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER, 0.0f);
glColor4ub(255,255,255,255);
int ax = 1;
int ay = 1;
if (1 >= 1)
ay = 0;
float tx = (float)ax / 7.0;
float ty = (float)ay / 1.0;
glBegin(GL_QUADS);
glTexCoord2f(tx,      ty+1.0); glVertex2i(obama2.cx+w, obama2.cy-ht);
glTexCoord2f(tx,      ty+0);    glVertex2i(obama2.cx+w, obama2.cy+ht);
glTexCoord2f(tx+1.0, ty+0);    glVertex2i(obama2.cx-w, obama2.cy+ht);
glTexCoord2f(tx+1.0, ty+1.0); glVertex2i(obama2.cx-w, obama2.cy-ht);
glEnd();
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_ALPHA_TEST);
}


void show_obama3()
{
if (gl.initDone == 0) {
float x = gl.xres/1;
x = x-60; //x cord
}
//obama.cx = 200;   charceter.cx is to make him follow megaman
obama3.cy = 300; // y cord
float ht = 75.0;//height of mari
float w = ht*0.5;

glPushMatrix();
glColor3f(1.0, 1.0, 1.0);
glBindTexture(GL_TEXTURE_2D, gl.obama_Texture3);
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER, 0.0f);
glColor4ub(255,255,255,255);
int ax = 1;
int ay = 1;
if (1 >= 1)
ay = 0;
float tx = (float)ax / 7.0;
float ty = (float)ay / 1.0;
glBegin(GL_QUADS);
glTexCoord2f(tx,      ty+1.0); glVertex2i(obama3.cx+w, obama3.cy-ht);
glTexCoord2f(tx,      ty+0);    glVertex2i(obama3.cx+w, obama3.cy+ht);
glTexCoord2f(tx+1.0, ty+0);    glVertex2i(obama3.cx-w, obama3.cy+ht);
glTexCoord2f(tx+1.0, ty+1.0); glVertex2i(obama3.cx-w, obama3.cy-ht);
glEnd();
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_ALPHA_TEST);
}
*/										




void show_sun()
{
    if (gl.initDone == 0) {
	float x = gl.xres/1;
	x = x-60; //x cord
    }
    sun.cx = 200;   //charceter.cx is to make him follow megaman
    sun.cy = 400; // y cord
    float ht = 75.0;//height of mari
    float w = ht*0.5;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.sun_Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 7.0;
    float ty = (float)ay / 1.0;
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+1.0); glVertex2i(sun.cx+w, sun.cy-ht);
    glTexCoord2f(tx,      ty+0);    glVertex2i(sun.cx+w, sun.cy+ht);
    glTexCoord2f(tx+1.0, ty+0);    glVertex2i(sun.cx-w, sun.cy+ht);
    glTexCoord2f(tx+1.0, ty+1.0); glVertex2i(sun.cx-w, sun.cy-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}


void show_shooting_star()
{
    int y = 450; //this might be it
    float ht = 50.0;//height of mari
    float w = ht*0.9;  //was .5

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.shooting_star_Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);  
    int ax = gl.ss_walkFrame % 64;  //animation  
    int ay = 0;


    if (gl.m_walkFrame >= 64){
	//if animation reaches LAST sprite
	//start from start again
	ay = 1;
    }
    float tx = (float)ax / 64.0;
    float ty = (float)ay / 8.0;

    glBegin(GL_QUADS);    
    //12.5
    glTexCoord2f(tx,      ty+.09); glVertex2i(shooting_star.cx- ss_position +w, y-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(shooting_star.cx- ss_position+w, y+ht);
    glTexCoord2f(tx+.14, ty);    glVertex2i(shooting_star.cx -ss_position -w, y+ht);
    glTexCoord2f(tx+.14, ty+.09); glVertex2i(shooting_star.cx - ss_position -w, y-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}



void quickSort(int*, int, int);
void bubbleSort(int*, int);
void selectionSort(int*, int);
void Merge(int*,int,int,int);
void MergeSort(int*,int,int);
void heapSort(int arr[],int n);
void heapify(int arr[], int n, int i);


void bubbleSort(int* arr, int size){
    int temp;
    for(int i = 0; i <size; i++){
	for(int j = 0; j < size - i - 1; j++){
	    if(arr[j] > arr[j+1]){
		temp = arr[j];
		arr[j] = arr[j+1];
		arr[j+1] = temp;
	    }
	}
    }
}


void selectionSort(int* arr, int n)
{
    //pos_min is short for position of min
    int pos_min,temp;

    for (int i=0; i < n-1; i++)
    {
	pos_min = i;//set pos_min to the current index of array

	for (int j=i+1; j < n; j++)
	{

	    if (arr[j] < arr[pos_min])
		pos_min=j;
	    //pos_min will keep track of the index that min is in, 
	    //this is needed when a swap happens
	}

	//if pos_min no longer equals i than a smaller value must have been found, 
	//so a swap must occur
	if (pos_min != i)
	{
	    temp = arr[i];
	    arr[i] = arr[pos_min];
	    arr[pos_min] = temp;
	}
    }
}



void Merge(int *a, int low, int high, int mid)
{
    // We have low to mid and mid+1 to high already sorted.
    int i, j, k, temp[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;

    // Merge the two parts into temp[].
    while (i <= mid && j <= high)
    {
	if (a[i] < a[j])
	{
	    temp[k] = a[i];
	    k++;
	    i++;
	}
	else
	{
	    temp[k] = a[j];
	    k++;
	    j++;
	}
    }

    // Insert all the remaining values from i to mid into temp[].
    while (i <= mid)
    {
	temp[k] = a[i];
	k++;
	i++;
    }

    // Insert all the remaining values from j to high into temp[].
    while (j <= high)
    {
	temp[k] = a[j];
	k++;
	j++;
    }


    // Assign sorted data stored in temp[] to a[].
    for (i = low; i <= high; i++)
    {
	a[i] = temp[i-low];
    }
}           



void MergeSort(int *a, int low, int high)
{
    int mid;
    if (low < high)
    {
	mid=(low+high)/2;
	// Split the data into two half.
	MergeSort(a, low, mid);
	MergeSort(a, mid+1, high);
	//
	//                         // Merge them to get sorted output.
	Merge(a, low, high, mid);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
	largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
	largest = r;

    // If largest is not root
    if (largest != i)
    {
	swap(arr[i], arr[largest]);

	// Recursively heapify the affected sub-tree
	heapify(arr, n, largest);
    }
}



void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
	heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
	// Move current root to end
	swap(arr[0], arr[i]);

	// call max heapify on the reduced heap
	heapify(arr, i, 0);
    }
}


void quickSort(int* arr, int start, int end){
    int temp;
    int i = start;
    int j = end;
    int pivot = arr[(start + end) / 2];

    while(i <= j){
	while(arr[i] < pivot){
	    i++;
	}
	while(arr[j] > pivot){
	    j--;
	}
	if(i <= j){
	    temp = arr[i];
	    arr[i] = arr[j];
	    arr[j] = temp;
	    i++;
	    j--;
	}
    }

    if(start < j){
	quickSort(arr, start, j);
    }
    if(i < end){
	quickSort(arr, i, end);
    }
}

// random algorithm every time
// FIX the IF() spaces !!!!!


class IntQueue{
    private:
	int *array;
	int size;
	int front;
	int back;
	int items;
    public:
	IntQueue(int);
	IntQueue(const IntQueue &);
	~IntQueue();

	void enqueue(int);
	void dequeue(int &);
	bool isEmpty();
	bool isFull();
	void clear();
};



IntQueue::IntQueue(int temp){
    array= new int[temp];
    size=temp;
    front= -1;
    back= -1;
    items=0;
}

IntQueue::IntQueue(const IntQueue &obj){
    front = obj.front;
    back = obj.back;
    items = obj.items;
    size = obj.size;

    array= new int[obj.size];
    for(int count=0; count < obj.size; count++){
	array[count] = *(array + count);
    }
}

IntQueue::~IntQueue(){
    delete [] array;
}

void IntQueue::enqueue(int elem){
    if(isFull()){
	cout << "queue is full\n";
	return;
    }else{
	back++;
	//rear = (rear+1) % size;
	array[back]= elem;
	items++;
    }
}

void IntQueue::dequeue(int &recover){
    if(isEmpty()){
	cout << "is empty\n";
    }else{
	front++;
	recover= array[front];
	items--;
    }
}

bool IntQueue::isEmpty(){
    return(items >= 0?true:false);

    /*   if(items >= 0){
	 return false;
	 }else{
	 return true;
	 }*/
}

bool IntQueue::isFull(){
    return(items < size?true:false);


    /*if(items < size){
      return false;
      }else{
      return true;
      }*/
}

void IntQueue::clear(){
    front = size-1;
    back = size-1;
    items = 0;
}



void init_round2(){
    //use random generator 
    //store values from RG
    //place them in a queue OR a stack
    //int a;
    //int b;
    //int c;
    //int ar[] = {a,b,c};

    //cherka

    int i =0;
    int catcher;
    const int SIZE = 3;
    IntQueue Q(SIZE);

    for(i=0; i<SIZE; i++){
	Q.enqueue(i*5);
    }


    //get two-three Obamas on different parts of the screen
    for(i=0; i < SIZE; i++){
	Q.dequeue(catcher);
	//if(i == 0)
	    //a = catcher;
	//if(i==1)
	    //b = catcher;
	//if(i==2)
	    //c = catcher;
    }

    //female.cx =

}



void CesarInit(){

    //find POSITIONS of where you want them to be

    //dummy numbers right now 
    srand(time(NULL));
    int random_number = rand() % 5 + 1;


    switch(random_number){
	case 1:
	    //bubble
	    bubbleSort(array,size);
	    break;
	case 2:
	    //selection
	    selectionSort(array,size);
	    break;
	case 3:
	    //Insertion
	    MergeSort(array, 0, size-1);
	    break;
	case 4:
	    //quick
	    quickSort(array, start, size-1);
	case 5:
	    //heap
	    heapSort(array, size);
	    break;
    }

    // once it is fully ready

    /*
       sun.cx = array[0];
       obama.cx = array[1];
       female.cx = array[2];
       mari.cx = array[3];
       shooting_star = array[4];
       */

    shooting_star.cx = *(array + 0);
    shooting_star.cy = *(array + 1);

    mariEnemy.cx = *(array + 2);
    mariEnemy.cy = 0;

    init_round2();
}

