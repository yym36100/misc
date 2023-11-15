/*
   Name: GLSAMPLE
   Author: Blaine Hodge
   Description: OpenGL sample. Read the file Include\Gl\ReadMe.txt
                for informations on using OpenGL.
   Date: -
   Copyright: Public domain
*/

// Includes

#include <windows.h>
#include <gl/gl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
//#include <unistd.h>

#include "cube_texture_and_coords.h"
#include "icosa.h"
#include "tex.h"

#       pragma comment (lib,"opengl32.lib")

#define PATH "./"

#define IMAGE_SIZE 128

#ifndef M_PI
   #define M_PI 3.141592654
#endif

typedef unsigned long uint32_t;
typedef struct
{
   uint32_t screen_width;
   uint32_t screen_height;
// OpenGL|ES objects

   GLuint tex[6];
// model rotation vector and direction
   GLfloat rot_angle_x_inc;
   GLfloat rot_angle_y_inc;
   GLfloat rot_angle_z_inc;
// current model rotation angles
   GLfloat rot_angle_x;
   GLfloat rot_angle_y;
   GLfloat rot_angle_z;
// current distance from camera
   GLfloat distance;
   GLfloat distance_inc;
// pointers to texture buffers
   char *tex_buf1;
   char *tex_buf2;
   char *tex_buf3;
} CUBE_STATE_T;

static void init_ogl(CUBE_STATE_T *state);
static void init_model_proj(CUBE_STATE_T *state);
static void reset_model(CUBE_STATE_T *state);
static GLfloat inc_and_wrap_angle(GLfloat angle, GLfloat angle_inc);
static GLfloat inc_and_clip_distance(GLfloat distance, GLfloat distance_inc);
static void redraw_scene(CUBE_STATE_T *state);
static void update_model(CUBE_STATE_T *state);
static void init_textures(CUBE_STATE_T *state);
static void load_tex_images(CUBE_STATE_T *state);
static void exit_func(void);
static volatile int terminate;
static CUBE_STATE_T _state, *state=&_state;

/***********************************************************
 * Name: init_ogl
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description: Sets the display, OpenGL|ES context and screen stuff
 *
 * Returns: void
 *
 ***********************************************************/
static void init_ogl(CUBE_STATE_T *state)
{
    state->screen_width = 512;
    state->screen_height = 512;

   // Set background color and clear buffers
   glClearColor(0.15f, 0.25f, 0.35f, 1.0f);

   // Enable back face culling.
  glEnable(GL_CULL_FACE);
 glEnable(GL_DEPTH_TEST);

   glMatrixMode(GL_MODELVIEW);
}

/***********************************************************
 * Name: init_model_proj
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description: Sets the OpenGL|ES model to default values
 *
 * Returns: void
 *
 ***********************************************************/
static void init_model_proj(CUBE_STATE_T *state)
{
   float nearp = 1.0f;
   float farp = 500.0f;
   float hht;
   float hwd;

   glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

   glViewport(0, 0, (GLsizei)state->screen_width, (GLsizei)state->screen_height);
      
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   hht = nearp * (float)tan(45.0 / 2.0 / 180.0 * M_PI);
   hwd = hht * (float)state->screen_width / (float)state->screen_height;

   glFrustum(-hwd, hwd, -hht, hht, nearp, farp);
   
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, vertices );

   reset_model(state);
}

/***********************************************************
 * Name: reset_model
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description: Resets the Model projection and rotation direction
 *
 * Returns: void
 *
 ***********************************************************/
static void reset_model(CUBE_STATE_T *state)
{
   // reset model position
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.f, 0.f, -2.f);

   // reset model rotation
   state->rot_angle_x = 45.f; state->rot_angle_y = 30.f; state->rot_angle_z = 0.f;
   state->rot_angle_x_inc = 0.005f; state->rot_angle_y_inc = 0.005f; state->rot_angle_z_inc = 0.001f;
   state->distance = 2.f;
}

/***********************************************************
 * Name: update_model
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description: Updates model projection to current position/rotation
 *
 * Returns: void
 *
 ***********************************************************/
static void update_model(CUBE_STATE_T *state)
{
   // update position
   state->rot_angle_x = inc_and_wrap_angle(state->rot_angle_x, state->rot_angle_x_inc);
   state->rot_angle_y = inc_and_wrap_angle(state->rot_angle_y, state->rot_angle_y_inc);
   state->rot_angle_z = inc_and_wrap_angle(state->rot_angle_z, state->rot_angle_z_inc);
   state->distance    = inc_and_clip_distance(state->distance, state->distance_inc);

   glLoadIdentity();
   // move camera back to see the cube
   glTranslatef(0.f, 0.f, -state->distance);

   // Rotate model to new position
   glRotatef(state->rot_angle_x, 1.f, 0.f, 0.f);
   glRotatef(state->rot_angle_y, 0.f, 1.f, 0.f);
   glRotatef(state->rot_angle_z, 0.f, 0.f, 1.f);
}

/***********************************************************
 * Name: inc_and_wrap_angle
 *
 * Arguments:
 *       GLfloat angle     current angle
 *       GLfloat angle_inc angle increment
 *
 * Description:   Increments or decrements angle by angle_inc degrees
 *                Wraps to 0 at 360 deg.
 *
 * Returns: new value of angle
 *
 ***********************************************************/
static GLfloat inc_and_wrap_angle(GLfloat angle, GLfloat angle_inc)
{
   angle += angle_inc;

   if (angle >= 360.0)
      angle -= 360.f;
   else if (angle <=0)
      angle += 360.f;

   return angle;
}

/***********************************************************
 * Name: inc_and_clip_distance
 *
 * Arguments:
 *       GLfloat distance     current distance
 *       GLfloat distance_inc distance increment
 *
 * Description:   Increments or decrements distance by distance_inc units
 *                Clips to range
 *
 * Returns: new value of angle
 *
 ***********************************************************/
static GLfloat inc_and_clip_distance(GLfloat distance, GLfloat distance_inc)
{
   distance += distance_inc;

   if (distance >= 120.0f)
      distance = 120.f;
   else if (distance <= 5.0f)
      distance = 5.0f;

   return distance;
}

/***********************************************************
 * Name: redraw_scene
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description:   Draws the model and calls eglSwapBuffers
 *                to render to screen
 *
 * Returns: void
 *
 ***********************************************************/
static void redraw_scene(CUBE_STATE_T *state)
{
   // Start with a clear screen
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   // Draw first (front) face:
   // Bind texture surface to current vertices
   glBindTexture(GL_TEXTURE_2D, state->tex[0]);

   // Need to rotate textures - do this by rotating each cube face
   glRotatef(270.f, 0.f, 0.f, 1.f ); // front face normal along z axis

   // draw first 4 vertices
   glDrawArrays( GL_TRIANGLES, 0, 180*3);
   
   glLoadIdentity();
   // move camera back to see the cube
  
   glTranslatef(2.f, 0.f, -5);
   glRotatef(state->rot_angle_y, 1.f, 0.2f, 0.4f);
   
   
   glDrawArrays( GL_TRIANGLES, 0, 180*3);

  

//   eglSwapBuffers(state->display, state->surface);
//     SwapBuffers( hDC );
}

/***********************************************************
 * Name: init_textures
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description:   Initialise OGL|ES texture surfaces to use image
 *                buffers
 *
 * Returns: void
 *
 ***********************************************************/
static void init_textures(CUBE_STATE_T *state)
{
   // load three texture buffers but use them on six OGL|ES texture surfaces
   load_tex_images(state);
   glGenTextures(6, &state->tex[0]);

   // setup first texture
   glBindTexture(GL_TEXTURE_2D, state->tex[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf1);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // setup second texture - reuse first image
   glBindTexture(GL_TEXTURE_2D, state->tex[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf1);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // third texture
   glBindTexture(GL_TEXTURE_2D, state->tex[2]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf2);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // fourth texture  - reuse second image
   glBindTexture(GL_TEXTURE_2D, state->tex[3]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf2);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   //fifth texture
   glBindTexture(GL_TEXTURE_2D, state->tex[4]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf3);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // sixth texture  - reuse third image
   glBindTexture(GL_TEXTURE_2D, state->tex[5]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf3);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // setup overall texture environment
   glTexCoordPointer(2, GL_FLOAT, 0, uvmaps);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   
   glEnable(GL_TEXTURE_2D);
}

/***********************************************************
 * Name: load_tex_images
 *
 * Arguments:
 *       void
 *
 * Description: Loads three raw images to use as textures on faces
 *
 * Returns: void
 *
 ***********************************************************/
static void load_tex_images(CUBE_STATE_T *state)
{
   FILE *tex_file1 = NULL, *tex_file2=NULL, *tex_file3 = NULL;
   int bytes_read, image_sz = IMAGE_SIZE*IMAGE_SIZE*3;
   int image_sz2 = 256*256*3;

   state->tex_buf1 = (char*)malloc(image_sz);
   state->tex_buf2 = (char*)malloc(image_sz);
   state->tex_buf3 = (char*)malloc(image_sz2);

   tex_file1 = fopen(PATH "Lucca_128_128.raw", "rb");
   if (tex_file1 && state->tex_buf1)
   {
      bytes_read=fread(state->tex_buf1, 1, image_sz, tex_file1);
      assert(bytes_read == image_sz);  // some problem with file?
      fclose(tex_file1);
   }

   tex_file2 = fopen(PATH "Djenne_128_128.raw", "rb");
   if (tex_file2 && state->tex_buf2)
   {
      bytes_read=fread(state->tex_buf2, 1, image_sz, tex_file2);
      assert(bytes_read == image_sz);  // some problem with file?
      fclose(tex_file2);      
   }

   tex_file3 = fopen(PATH "ExportedFont.raw", "rb");
   if (tex_file3 && state->tex_buf3)
   {
      bytes_read=fread(state->tex_buf3, 1, image_sz2, tex_file3);
      assert(bytes_read == image_sz2);  // some problem with file?
      fclose(tex_file3);
   }   
}
	
	
// Function Declarations

LRESULT CALLBACK 
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
VOID DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

// WinMain
void DrawText(GLfloat x, GLfloat y, char *text)
{
     #define char_x_size (32)
     #define char_y_size (20)
     
     char t1,*t = text;
     int i = 0;
     //GLfloat *vertex;
     //GLfloat *texmap;
     int len = strlen(text);
     GLfloat u,v;
     
     //vertex = new GLfloat[3*6*len];
     //texmap = new GLfloat[2*6*len];

	 GLfloat vertex[3*6*11];
     GLfloat texmap[2*6*11];
     
     while(*t)
     {
        //add char
        t1 =  *t-32;
        v = t1 / 8;
        u = t1 % 8;
        
        v *=char_y_size;
        u *=char_x_size;

		u /= 256.0;
		v /= 256.0;
        
        //1
        vertex[i*3*6 + 0 + 0*3] = x;
        vertex[i*3*6 + 1 + 0*3] = y;
        vertex[i*3*6 + 2 + 0*3] = 0;
         
        texmap[i*2*6 + 0 + 0*2] = u ;
        texmap[i*2*6 + 1 + 0*2] = 1-v ;

		//2
        vertex[i*3*6 + 0 + 1*3] = x + char_x_size;
        vertex[i*3*6 + 1 + 1*3] = y ;
        vertex[i*3*6 + 2 + 1*3] = 0;
         
        texmap[i*2*6 + 0 + 1*2] = u + char_x_size/256.0;
        texmap[i*2*6 + 1 + 1*2] = 1-v ;
        
        //3
        vertex[i*3*6 + 0 + 2*3] = x;
        vertex[i*3*6 + 1 + 2*3] = y + char_y_size;
        vertex[i*3*6 + 2 + 2*3] = 0;
         
        texmap[i*2*6 + 0 + 2*2] = u ;
        texmap[i*2*6 + 1 + 2*2] = 1-(v + char_y_size/256.0);
        
       
        
        //4
        vertex[i*3*6 + 0 + 3*3] = x + char_x_size;
        vertex[i*3*6 + 1 + 3*3] = y + char_y_size;
        vertex[i*3*6 + 2 + 3*3] = 0;
         
        texmap[i*2*6 + 0 + 3*2] = u + char_x_size/256.0 ;
        texmap[i*2*6 + 1 + 3*2] = 1-(v + char_y_size/256.0);
        
        //5
        vertex[i*3*6 + 0 + 4*3] = x;
        vertex[i*3*6 + 1 + 4*3] = y + char_y_size;
        vertex[i*3*6 + 2 + 4*3] = 0;
        
        texmap[i*2*6 + 0 + 4*2] = u ;
        texmap[i*2*6 + 1 + 4*2] = 1-(v + char_y_size/256.0);

		//6
        vertex[i*3*6 + 0 + 5*3] = x + char_x_size;
        vertex[i*3*6 + 1 + 5*3] = y ;
        vertex[i*3*6 + 2 + 5*3] = 0;
         
        texmap[i*2*6 + 0 + 5*2] = u + char_x_size/256.0;
        texmap[i*2*6 + 1 + 5*2] = 1-v ;

   
        x += char_x_size;
        i++;
        t++;
     }    
    
    glVertexPointer( 3, GL_FLOAT, 0, vertex );
    glTexCoordPointer(2, GL_FLOAT, 0, texmap);
    
    glLoadIdentity();
    // move camera back to see the cube
    glTranslatef(0.f, 0.f, -180);
    //glRotatef(180,0,0,1);
    glScalef(0.2,0.2,1);
        
    glDrawArrays( GL_TRIANGLES, 0, len*3*6);
           
     
    // delete[] vertex;
     //delete[] texmap;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int iCmdShow)
{
  WNDCLASS wc;
  HWND hWnd;
  HDC hDC;
  HGLRC hRC;    
  MSG msg;
  BOOL bQuit = FALSE;
  float theta = 0.0f;
  

  // register window class
  wc.style = CS_OWNDC;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
  wc.hCursor = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "GLSample";
  RegisterClass( &wc );

  // create main window
  hWnd = CreateWindow( 
  "GLSample", "OpenGL Sample", 
  WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
  0, 0, 512, 512,
  NULL, NULL, hInstance, NULL);

  // enable OpenGL for the window
  EnableOpenGL( hWnd, &hDC, &hRC );

 // Start OGLES
   init_ogl(state);

   // Setup the model world
   init_model_proj(state);

   // initialise the OGLES texture(s)
   init_textures(state);
   
  // program main loop
  while (!bQuit) 
    {
      // check for messages
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
          // handle or dispatch messages
          if (msg.message == WM_QUIT) 
            {
              bQuit = TRUE;
            } 
          else 
            {
              TranslateMessage(&msg);
              DispatchMessage(&msg);
            }

         } 
      else 
        {
        // OpenGL animation code goes here
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
        glBindTexture(GL_TEXTURE_2D, state->tex[4]);
        
      DrawText(0,0,"Hello");
        
         glVertexPointer( 3, GL_FLOAT, 0, vertices3 );
         glTexCoordPointer(2, GL_FLOAT, 0, uvmaps3);
        
        
        
         glLoadIdentity();
        // move camera back to see the cube
        glTranslatef(0.f, 0.f, -30);
        glRotatef(180,0,0,1);
        glScalef(10,10,1);
        
      /*  glRotatef(90, 0.f, 1.f, 0.f);
         glRotatef(90, 0.f, 0.f, 1.f);
          glRotatef(-180, 0.f, 1.f, 0.f);
            glTranslatef(0.f, 0.f, 5);
           glRotatef(-theta, 0.f, 1.f, 0.f);
           theta+=0.01;*/
            
        
        // Rotate model to new position
        //glRotatef(state->rot_angle_x, 1.f, 0.f, 0.f);
        //   glRotatef(state->rot_angle_y, 0.f, 1.f, 0.f);
        //   glRotatef(state->rot_angle_z, 0.f, 0.f, 1.f);
        
        
        
        // Need to rotate textures - do this by rotating each cube face
       // glRotatef(270.f, 0.f, 0.f, 1.f ); // front face normal along z axis
        
        // draw first 4 vertices
       // glDrawArrays( GL_TRIANGLES, 0, 2*3);
         glBindTexture(GL_TEXTURE_2D, state->tex[0]);
        
        // update_model(state);
         glVertexPointer( 3, GL_FLOAT, 0, vertices );
         glTexCoordPointer(2, GL_FLOAT, 0, uvmaps);
        
        glLoadIdentity();
        // move camera back to see the cube
        glTranslatef(3.f, 0.f, -30);
        
        glRotatef(90, 0.f, 1.f, 0.f);
         glRotatef(90, 0.f, 0.f, 1.f);
          glRotatef(-180, 0.f, 1.f, 0.f);
            glTranslatef(0.f, 0.f, 5);
           glRotatef(-theta, 0.f, 1.f, 0.f);
           theta+=0.01;
            
        
        // Rotate model to new position
        //glRotatef(state->rot_angle_x, 1.f, 0.f, 0.f);
        //   glRotatef(state->rot_angle_y, 0.f, 1.f, 0.f);
        //   glRotatef(state->rot_angle_z, 0.f, 0.f, 1.f);
        
        
        
        // Need to rotate textures - do this by rotating each cube face
       // glRotatef(270.f, 0.f, 0.f, 1.f ); // front face normal along z axis
        
        // draw first 4 vertices
        glDrawArrays( GL_TRIANGLES, 0, 180*3);
        
         glVertexPointer( 3, GL_FLOAT, 0, vertices2 );
         glTexCoordPointer(2, GL_FLOAT, 0, uvmaps2);
        
          glLoadIdentity();
        // move camera back to see the cube
        glTranslatef(6.f, 0.f, -30);
        
        glRotatef(90, 0.f, 1.f, 0.f);
        glRotatef(90, 0.f, 0.f, 1.f);
        glRotatef(-180, 0.f, 1.f, 0.f);
        glRotatef(-theta/3.0, 0.f, 1.f, 0.f);
        glRotatef(-theta/2.0, 1.f, 0.f, 0.f);
//            glTranslatef(0.f, 0.f, 18);
        
        glDrawArrays( GL_TRIANGLES, 0, 20*3);
        
        
         glVertexPointer( 3, GL_FLOAT, 0, vertices );
         glTexCoordPointer(2, GL_FLOAT, 0, uvmaps);
         
        glLoadIdentity();
        glTranslatef(3.f, 2.f, -30);        
        glRotatef(90, 0.f, 1.f, 0.f);
        glRotatef(90, 0.f, 0.f, 1.f);
        glRotatef(-180, 0.f, 1.f, 0.f);
         glRotatef(-theta/3.0, 0.f, 1.f, 0.f);
         
          glDrawArrays( GL_TRIANGLES, 0, 180*3);
   
   
          //  redraw_scene(state);
            
            SwapBuffers( hDC );
            
            theta += 0.010f;

        }
  }
  // shutdown OpenGL
  DisableOpenGL( hWnd, hDC, hRC );
  // destroy the window explicitly
  DestroyWindow( hWnd );
  return msg.wParam;
}

// Window Procedure

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) 
    {
      case WM_CREATE:
        return 0;

      case WM_CLOSE:
        PostQuitMessage( 0 );
        return 0;

      case WM_DESTROY:
        return 0;

      case WM_KEYDOWN:
        switch (wParam) 
        {
          case VK_ESCAPE:
            PostQuitMessage( 0 );
            return 0;
        }
        return 0;

        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

// Enable OpenGL

VOID EnableOpenGL( HWND hWnd, HDC * hDC, HGLRC * hRC )
{
  PIXELFORMATDESCRIPTOR pfd;
  int iFormat;

  // get the device context (DC)
  *hDC = GetDC( hWnd );

  // set the pixel format for the DC
  ZeroMemory( &pfd, sizeof( pfd ) );
  pfd.nSize = sizeof( pfd );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DEPTH_DONTCARE;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  iFormat = ChoosePixelFormat( *hDC, &pfd );
  SetPixelFormat( *hDC, iFormat, &pfd );

  // create and enable the render context (RC)
  *hRC = wglCreateContext( *hDC );
  wglMakeCurrent( *hDC, *hRC );
}

// Disable OpenGL

VOID DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
  wglMakeCurrent( NULL, NULL );
  wglDeleteContext( hRC );
  ReleaseDC( hWnd, hDC );
} 
