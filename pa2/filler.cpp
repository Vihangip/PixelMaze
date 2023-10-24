/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"

#include "filler.h"

animation filler::fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    solidColorPicker s(fillColor);
    return fill<Stack>(img,x,y,s,tolerance,frameFreq);


}

animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    gridColorPicker g(gridColor,gridSpacing);
    return fill<Stack>(img,x,y,g,tolerance,frameFreq);

}

animation filler::fillGradientDFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    gradientColorPicker g(fadeColor1,fadeColor2,radius,x,y);
    return fill<Stack>(img,x,y,g,tolerance,frameFreq);

}


animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    /**
     *  Our code here!
     */

    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    solidColorPicker s(fillColor);
    return fill<Queue>(img,x,y,s,tolerance,frameFreq);
}

animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    gridColorPicker g(gridColor,gridSpacing);
    return fill<Queue>(img,x,y,g,tolerance,frameFreq);
}

animation filler::fillGradientBFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    gradientColorPicker g(fadeColor1,fadeColor2,radius,x,y);
    return fill<Queue>(img,x,y,g,tolerance,frameFreq);
}

animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    /**
     * Our code here!
     */
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. 
     *
     * To begin the algorithm, you simply:
     * a) place the given point in the ordering structure, 
     * marking it processed (the way you mark it is a design 
     * decision you'll make yourself).
     *
     * b) We have a choice to either change the color, if appropriate, 
     * when we * add the point to the OS, or when we take it off. 
     * In our test cases, * we have assumed that you will change 
     * the color when a point is added to the structure. 
     *
     * c) Add the first image to the animation (it's convenient to 
     * think of this as the 0th image). 
     *
     * THEN, until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        a.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the 
     *              center's color, to the ordering structure, set their
     *              new color, and mark them as processed.
     *        b.    if it is an appropriate frame, send the current 
     *              PNG to the animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore 
     *        neighboring pixels in some order.
     *
     *        While the order in which you examine neighbors does 
     *        not matter for a proper fill, you must use the same 
     *        order as we do for your animations to come out like 
     *        ours! The order you should put neighboring pixels 
     *        **ONTO** the queue or stack is as follows:
     *        RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). 
     *        IMPORTANT NOTE: *UP* here means towards the top of 
     *        the image, so since an image has smaller y coordinates 
     *        at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *
     *        To reiterate, when you are exploring 
     *        (filling out) from a given pixel, you must first try 
     *        to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then 
     *        again after the 8th pixel, etc.  You must only add 
     *        frames for the number of pixels that have been filled, 
     *        not the number that have been checked. So if frameFreq 
     *        is set to 1, a pixel should be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the 
     *        fill, and it will be the one we test against.
     */



    OrderingStructure<HSLAPixel> toVisit;
    vector<HSLAPixel> processed;

    OrderingStructure<int> xCoordinates;
    OrderingStructure<int> yCoordinates;

    int pixelsFilled = 0;
    animation anim;

    HSLAPixel ogPixel = *img.getPixel(x,y);
    toVisit.add(ogPixel);
    xCoordinates.add(x);
    yCoordinates.add(y);

    fillPixelColor(ogPixel,processed,x,y,img,fillColor,pixelsFilled);
    anim.addFrame(img);


    while(!toVisit.isEmpty()) {
        HSLAPixel curr = toVisit.remove();

        int currX = xCoordinates.remove();
        int currY = yCoordinates.remove();

        if(withinDistance(currX+1,currY,ogPixel,img,tolerance)){
            HSLAPixel pixel = *img.getPixel(currX+1,currY);
            toVisit.add(pixel);
            xCoordinates.add(currX+1);
            yCoordinates.add(currY);
        }

        if(withinDistance(currX,currY+1,ogPixel,img,tolerance)){
            HSLAPixel pixel = *img.getPixel(currX,currY+1);
            toVisit.add(pixel);
            xCoordinates.add(currX);
            yCoordinates.add(currY+1);
        }

        if(withinDistance(currX-1,currY,ogPixel,img,tolerance)){
            HSLAPixel pixel = *img.getPixel(currX-1,currY);
            toVisit.add(pixel);
            xCoordinates.add(currX-1);
            yCoordinates.add(currY);
        }

        if(withinDistance(currX,currY-1,ogPixel,img,tolerance)){
            HSLAPixel pixel = *img.getPixel(currX,currY-1);
            toVisit.add(pixel);
            xCoordinates.add(currX);
            yCoordinates.add(currY-1);
        }

        fillPixelColor(curr,processed,currX,currY,img,fillColor,pixelsFilled);

        addFrameToAnim(pixelsFilled,frameFreq,anim,img);


    }
    anim.addFrame(img);
    return anim;


}

void filler::addFrameToAnim(int& pixelsFilled, int frameFreq, animation &animation, PNG &img) {
    if(pixelsFilled == frameFreq) {
        animation.addFrame(img);
        pixelsFilled = 0;
    }

}

void filler::fillPixelColor(HSLAPixel pixel, vector<HSLAPixel>& processed, int x, int y, PNG &img, colorPicker &fillColor, int& pixelsFilled) {
    if(find(processed.begin(),processed.end(),pixel) == processed.end()){
        *(img.getPixel(x,y)) = fillColor(x,y);
        processed.push_back(*img.getPixel(x,y));
        pixelsFilled += 1;
    }

}

bool filler::withinDistance(int x, int y,HSLAPixel center, PNG &img, double tolerance) {
    bool within = false;
    int width = img.width();
    int height = img.height();

    HSLAPixel currPixel = *img.getPixel(x,y);
   //HSLAPixel centerPixel = *img.getPixel(centX,centY);

    double distance = center.dist(currPixel);


    //double distance = abs(centX - x) + abs(centY - y);

    if(x<= width && y<= height) {
        if(distance <= tolerance) {
            within = true;
        }
    }

    return within;
}


void fillPixelColor(HSLAPixel pixel,vector<HSLAPixel> processed,int x, int y,PNG& img,colorPicker& fillColor,int pixelsFilled){
    if(find(processed.begin(),processed.end(),pixel) != processed.end()){
        *(img.getPixel(x,y)) = fillColor(x,y);
        processed.push_back(*img.getPixel(x,y));
        pixelsFilled += 1;
    }

}

bool withinDistance(int x, int y,int centX, int centY, PNG &img,double tolerance) {
    bool within = false;
    int width = img.width();
    int height = img.height();

    double distance = abs(centX - x) + abs(centY - y);

    if(x<= width && y<= height) {
        if(distance <= tolerance) {
            within = true;
        }
    }

    return within;


}



