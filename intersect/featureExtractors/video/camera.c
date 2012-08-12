/**
 * Display video from webcam
 *
 * Author  Nash
 * License GPL
 * Website http://nashruddin.com
 */
 
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
 
int main( int argc, char **argv )
{
    CvCapture *capture = 0;
    IplImage  *frame = 0;
    int       key = 0;
 
    /* initialize camera */
    capture = cvCaptureFromCAM(CV_CAP_ANY);
//    capture = 1;
 
    /* always check */
    if ( !capture ) {
        fprintf( stderr, "Cannot initialize the goddamn webcam!\n" );
        return 1;
    }
 
    /* create a window for the video */
    cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );
 
    while( key != 'q' ) {
        /* get a frame */
        frame = cvQueryFrame( capture );
 
        /* always check */
        if( !frame ) break;
       
        /* display current frame */
        cvShowImage( "result", frame );
 
        /* exit if user press 'q' */
        key = cvWaitKey( 1 );
    }
 
    /* free memory */
    cvDestroyWindow( "result" );
    cvReleaseCapture( &capture );
 
    return 0;
}
