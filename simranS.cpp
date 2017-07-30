//Simran Preet Singh
//
//
//
//06/24/17
//What does this code do?
//This code makes sound using audio files the library is used to do this
//is openal and this code displays two enemies using ppm images
//The enemies do not do much but they show up on the screen.
//====================================================================
//
//07/20/17
//I added godzilla and its walk physics yea
#include <iostream>
#include <stdio.h>
#include <cstdlib>
//#include <string>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <time.h>
#include "game.h"
#include "ppm.h"
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif

using namespace std;


int i = -400;

int birdm = -400;

int birdy= -300;

class T {

    public:
	double prate;
	double obi;
	struct timespec ts, te,tc;
	struct timespec wt;
	T() {
	    prate=1.0/30.0;
	    obi=1.0/1e9;
	}
	double td(struct timespec *start, struct timespec *end) {
	    return (double)(end->tv_sec - start->tv_sec) + 
		(double)(end->tv_nsec - start->tv_nsec) * obi;
	}
	void tcpy(struct timespec *dest, struct timespec *source) {
	    memcpy(dest, source, sizeof(struct timespec));
	}
	void rt(struct timespec *t) {
	    clock_gettime(CLOCK_REALTIME, t);
	}

} t, ti;


//This flag is used for checking if the dsound fuction is called
//if it is called then it will delete the source and buffer
bool h = false;

//This function plays sound using openal's function alSource Play(...)

void Playsound(ALuint tum) 
{
    alSourcePlay(tum);
}

//This function creates sound and checks if the libraries are found
//This function also deletes the buffer and source of sound if 
//the boolean value is true
void csound(const char *a) 
{

#ifdef USE_OPENAL_SOUND
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
	printf(" There is an error  in alutInit()\n");
	return;
    }

    alGetError();

    float termoil[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, termoil);
    alListenerf(AL_GAIN, 1.0);

    ALuint toom;
    toom = alutCreateBufferFromFile(a); 

    ALuint tum;

    alGenSources(1, &tum);
    alSourcei(tum, AL_BUFFER, toom);

    alSourcef(tum, AL_GAIN, 0.20);
    alSourcef(tum, AL_PITCH, 1.0);
    alSourcei(tum, AL_LOOPING, 0);

    if (alGetError() != AL_NO_ERROR) {
	printf("cannot set the source\n");
	return;
    }
    Playsound(tum);
    if(h == true) {
	alDeleteSources(1, &tum);
	alDeleteBuffers(1, &toom);
    }
#endif
}

//this function closes and destroyes the sound
void dsound()
{ 
#ifdef USE_OPENAL_SOUND
    h = true;

    ALCcontext *stuff = alcGetCurrentContext();
    ALCdevice *yantar = alcGetContextsDevice(stuff);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(stuff);
    alcCloseDevice(yantar);

#endif
}

//This function converts a png image to a ppm image
Ppmimage *turretImage() 
{
    system ("convert ./images/Turret.png ./images/Turret.ppm");
    return ppm6GetImage("./images/Turret.ppm");
}

//This function displays a turret on to the screen
void showTurret() 
{
    //glClearColor(0.1,0.1,0.1,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    //float x = gl.xres/1.5;
    float y = 100;
    float ht = 20.0;
    float w = ht*2;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.turretTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 4.0;
    float ty = (float)ay;

    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+.5); glVertex2i(turret.cx+w, y-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(turret.cx+w, y+ht);
    glTexCoord2f(tx+.5, ty);    glVertex2i(turret.cx-w, y+ht);
    glTexCoord2f(tx+.5, ty+.5); glVertex2i(turret.cx-w, y-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

//This function converts a png image to a ppm image
Ppmimage *enemy1image()
{
    system ("convert ./images/enemy1.png ./images/enemy1.ppm");
    return ppm6GetImage("./images/enemy1.ppm");
}

//this function displays an enemy
//curretly the enemey has srounded the hero
void showenemy1() 
{
    //float x = gl.xres/2.0;
    float y = 100;
    float ht = 30.0;
    float w = ht*2;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.enemy1Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 4.0;
    float ty = (float)ay;

    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+.5); glVertex2i(enemy1.cx+w, y-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(enemy1.cx+w, y+ht);
    glTexCoord2f(tx+.5, ty);    glVertex2i(enemy1.cx-w, y+ht);
    glTexCoord2f(tx+.5, ty+.5); glVertex2i(enemy1.cx-w, y-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void godzillaphysics(void)
{
    t.rt(&t.tc);
    double tspan = t.td(&t.wt, &t.tc);
    if (tspan > gl.godzilladelay) {
	gl.godzillawf++;
	i++;
	if (gl.godzillawf >= 3) {
	    gl.godzillawf -= 3;
	    i--;
	}
	t.rt(&t.wt);
    }
}


Ppmimage *godzillaimage()
{
    system ("convert ./images/godzilla.png ./images/godzilla.ppm");
    return ppm6GetImage("./images/godzilla.ppm");
}

Ppmimage *godzillaballimage()
{
        system ("convert ./images/godzillaball.png ./images/godzillaball.ppm");
	    return ppm6GetImage("./images/godzillaball.ppm");
}


//this function displays an enemy
//curretly the enemey has srounded the hero
void showgodzilla()
{
    //float x = gl.xres/2.0;
    float y = 160;
    float ht = 100.0;
    float w = ht*2;
    int move = 2133;



    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.godzillaTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    int ax = gl.godzillawf % 3;
    int ay = 0;
    if (gl.godzillawf >= 3) {
	ay = 1;
    }
    float tx = (float)ax / 3.0;
    float ty = (float)ay/ 1.0;
    int a = godzilla.cx+i+move;
    int b = godzilla.cx+i+move;

    cout << "\n\n\n\n\n\n\n\n\n" << a <<"\n\n\n\n\n\n\n\n\n" << b << "\n\n\n\n\n";

    if (i > -950) {
	i--;
	glBegin(GL_QUADS);
	glTexCoord2f(tx-.334,      ty+1.0); 
	glVertex3s(godzilla.cx+i+move+w, y-ht,0);
	glTexCoord2f(tx-.334,      ty);    
	glVertex3s(godzilla.cx+i+move+w, y+ht,0);
	glTexCoord2f(tx, ty);    glVertex3s(godzilla.cx+i+move-w, y+ht,0);
	glTexCoord2f(tx, ty+1.0); glVertex3s(godzilla.cx+i+move-w, y-ht,0);


	/*gl.godzillaP[gl.godzillaPcount].cx = godzilla.cx+i+move-w;
	gl.godzillaP[gl.godzillaPcount].cy = y-ht;
	gl.godzillaP[gl.godzillaPcount].velocity = gl.particleVelocity;
	gl.godzillaPcount++;



	for (int j = 0; j < gl.godzillaPcount; j++) {
	     gl.godzillaP[j].cx = godzilla.cx+i+move-w;
	}

	for (int j = 0; j < gl.godzillaPcount; j++) {
        
	glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(gl.godzillaP[i].cx, gl.godzillaP[i].cy, 0);
        float w = gl.godzillaPw;
        float h = gl.godzillaPh;
        glBindTexture(GL_TEXTURE_2D, gl.godzillaballTexture);
        glEnable(GL_ALPHA_TEST);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0); glVertex2i(-w, -h);
        glTexCoord2f(0.0, 0.0); glVertex2i(-w,  h);
        glTexCoord2f(1.0, 0.0); glVertex2i(w,   h);
        glTexCoord2f(1.0, 1.0); glVertex2i(w,  -h);
        glEnd();
        glPopMatrix();
        glDisable(GL_ALPHA_TEST);
        
	//gl.godzillaP[i].cx+i+move-w = gl.godzillaP[i].cx+i+move-w - gl.particle[i].velocity;
        if (gl.godzillaP[i].cx < 0 || gl.godzillaP[i].cx > gl.xres) {
                gl.godzillaP[i] = gl.godzillaP[gl.godzillaPcount - 1];
                gl.godzillaPcount--;
        }*/



	
	}

	if (mainChar.cx >= godzilla.cx+i+move-w &&
	    mainChar.cx <= godzilla.cx+i+move+w) {
	    if (mainChar.cy <= y-ht || mainChar.cy >= y+ht || mainChar.cy == y+ht 
		    || mainChar.cy == y-ht) {
		mainChar.health = mainChar.health;
	    } else {
		//mainChar.health--;
	    }
	}


	if( i < -949) {
	    i = -1099;
	}

    if ( i < -950) { 
	i++;
	glBegin(GL_QUADS);
	glTexCoord2f(tx+.33,      ty+1.0); 
	glVertex3s(godzilla.cx+i+move+w, y-ht,0);
	glTexCoord2f(tx+.33,      ty);    
	glVertex3s(godzilla.cx+i+move+w, y+ht,0);
	glTexCoord2f(tx, ty);    glVertex3s(godzilla.cx+i+move-w, y+ht,0);
	glTexCoord2f(tx, ty+1.0); glVertex3s(godzilla.cx+i+move-w, y-ht,0);

	if (mainChar.cx <= godzilla.cx+i+move-w && 
	    mainChar.cx >= godzilla.cx+i+move+w) {

	    if (mainChar.cy <= y-ht || mainChar.cy >= y+ht || mainChar.cy == y+ht 
		                        || mainChar.cy == y-ht) {
		mainChar.health = mainChar.health;
	    } else {
		//mainChar.health--;
	    }
	}


	if (i > -951) {
	    i = -800;
	}
    }





    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);

}

void birdphysics(void)
{
    ti.rt(&ti.tc);
    double tspan = ti.td(&ti.wt, &ti.tc);
    if (tspan > gl.birddelay) {
        gl.birdwf++;
        birdm++;
	birdy--;
        if (gl.birdwf >= 4) {
            gl.birdwf -= 4;
            birdm--;
	    birdy++;
        }
        ti.rt(&ti.wt);
    }
}



Ppmimage *birdImage()
{
        system ("convert ./images/bird.png ./images/bird.ppm");
	    return ppm6GetImage("./images/bird.ppm");
}

void showbird()
{
    //float x = gl.xres/2.0;
    float y = 100;
    float ht = 30.0;
    float w = ht*2;
    int move = 1700;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.birdTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    int ax = gl.birdwf % 4;
    int ay = 0;
    if (gl.birdwf >= 4) {
        ay = 1;
}
    float tx = (float)ax / 4.0;
    float ty = (float)ay / 1.0;

    if(birdm > -950) {
    birdy++;
    birdm--;
    glBegin(GL_QUADS);
    glTexCoord2f(tx+.25,      ty+1); glVertex2i(bird.cx+birdm+move+w, y+birdy-ht);
    glTexCoord2f(tx+.25,      ty);    glVertex2i(bird.cx+birdm+move+w, y+birdy+ht);
    glTexCoord2f(tx, ty);    glVertex2i(bird.cx+birdm+move-w, y+birdy+ht);
    glTexCoord2f(tx, ty+1); glVertex2i(bird.cx+birdm+move-w, y+birdy-ht); 
    if (birdm < -949) {
	birdm = -1099;
    }
    }
    
    if ( birdm < -950) {
    birdm++;
    birdy--;
    glBegin(GL_QUADS);
    glTexCoord2f(tx-.25,      ty+1); glVertex2i(bird.cx+birdm+move+w, y+birdy-ht);
    glTexCoord2f(tx-.25,      ty);    glVertex2i(bird.cx+birdm+move+w, y+birdy+ht);
    glTexCoord2f(tx, ty);    glVertex2i(bird.cx+birdm+move-w, y+birdy+ht);
    glTexCoord2f(tx, ty+1); glVertex2i(bird.cx+birdm+move-w, y+birdy-ht);

    if (birdm > -951) {
	birdm = -800;
    }
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

