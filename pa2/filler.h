/**
 * @file filler.h
 * Defintion of a filler namespace.
 *
 */
#ifndef _FILLER_H_
#define _FILLER_H_

#include "cs221util/PNG.h"
#include "stack.h"
#include "queue.h"
#include "solidColorPicker.h"
#include "gridColorPicker.h"
#include "gradientColorPicker.h"
#include "rainbowColorPicker.h"
#include "animation.h"
using namespace cs221util;

/**
 * filler namespace: specifies a set of functions for performing flood
 * fills on images. A namespace is a mechanism for placing several
 * functions within the same "scope". To call the functions in 
 * the namespace, you simply preface them with "filler::".
 *
 */
namespace filler
{
        /**
         * Performs a flood fill on the given image using a solid color,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color of the fill.
         * @param tolerance How far away colors are allowed to be to
         *  still be included in the fill.
         * @param frameFreq How frequently to add a frame to the
         *  animation, in pixels. For instance, if frameFreq == 1, a frame is
         *  added when every pixel is filled. If frameFreq == 10, a frame is
         *  added after every 10 pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a grid,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param gridColor The color the lines of the grid should appear.
         * @param gridSpacing The width and height of the cells of the grid.
         * @param tolerance How far away colors are allowed to be to 
         * still be included in the fill.
         * @param frameFreq How frequently to add a frame to the 
         * animation, in pixels. For instance, if frameFreq == 1, 
         * a frame is added when every pixel is filled. If 
         * frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         *
         * @return An animation that shows the fill progressing 
         * over the image.
         */
        animation fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                           int gridSpacing, double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a gradient, employing
         * a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fadeColor1 The starting color of the gradient.
         * @param fadeColor2 The ending color of the gradient.
         * @param radius The radius for the gradient.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGradientDFS(PNG& img, int x, int y, HSLAPixel fadeColor1,
                HSLAPixel fadeColor2, int radius, double tolerance,
                int frameFreq);

        /**
         * Performs a flood fill on the given image using a solid color,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color of the fill.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a grid, employing a
         * breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param gridColor The color the lines of the grid should appear.
         * @param gridSpacing The width and height of the cells of the grid.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                int gridSpacing, double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a gradient,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fadeColor1 The starting color of the gradient.
         * @param fadeColor2 The ending color of the gradient.
         * @param radius The radius for the gradient.
         * @param tolerance How far away colors are allowed to be to still
         *  be included in the fill.
         * @param frameFreq How frequently to add a frame to the animation,
         *  in pixels. For instance, if frameFreq == 1, a frame is added
         *  when every pixel is filled. If frameFreq == 10, a frame is added
         *  after every 10 pixels is filled.
         * @return An animation that shows the fill progressing over the
         *  image.
         */
        animation fillGradientBFS(PNG& img, int x, int y, HSLAPixel fadeColor1,
                HSLAPixel fadeColor2, int radius, double tolerance,
                int frameFreq);

        /* The following two functions are given to you as examples of 
         * working fill functions. 
        */
        animation fillRainDFS(PNG& img, int x, int y, long double freq, double tolerance, int frameFreq);

        animation fillRainBFS(PNG& img, int x, int y, long double freq, double tolerance, int frameFreq);


    /**
     * General filling function: a general helper that should be invoked by
     * all of the public fill functions with the appropriate color picker
     * for that type of fill.
     *
     * For examples, a) filler::dfs::fillSolid should call fill with the
     * correct ordering structure as its template parameter, passing in a
     * solidColorPicker object.
     *
     * b) filler::bfs::fillGradient should call fill with a different 
     * ordering structure as its template parameter, passing in a
     * gradientColorPicker object.
     *
     * @param img Image to do the filling on.
     * @param x X coordinate to start the fill from.
     * @param y Y coordinate to start the fill from.
     * @param fillColor The colorPicker to be used for the fill.
     * @param tolerance How far away colors are allowed to be to still be
     *  included in the fill.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. For instance, if frameFreq == 1, a frame is added when every
     *  pixel is filled. If frameFreq == 10, a frame is added after every 10
     *  pixels is filled.
     * @return An animation that shows the fill progressing over the image.
     * 
     * Note: implementation instructions are in the .cpp file
     *
     */
    template <template <class T> class OrderingStructure>
    animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                   double tolerance, int frameFreq);

//    /** checks if the given pixel is within the tolerance distance and image
//     */
//    bool withinDistance(int x, int y,HSLAPixel center, PNG &img,double tolerance);
//
//    void fillPixelColor(HSLAPixel pixel,vector<HSLAPixel>& processed,int x, int y,PNG& img,colorPicker& fillColor,int& pixelsFilled);
//
//    void addFrameToAnim(int& pixelsFilled, int frameFreq,animation& animation,PNG& img);

    struct PixelStatus{
        int x;
        int y;
        HSLAPixel pixelBeforeProcessed;
        bool isProcessed;
    };

    /* effects: If pixel of given (x, y) is unprocessed, and is within
     *          boundary of given image, and is within fill region,
     *          then adds its PixelStatus to given ordering structure,
     *          marks it as processed, and fills it with given color picker.
     *          Returns true if pixel of given (x, y) is actually filled.
     *          If given pixel fails any condition above then return false.
     */
    bool fillPixel(int x, int y,
                   int ctr_x, int ctr_y, double tolerance,
                   vector<vector<PixelStatus>>& imgMatrix,
                   OrderingStructure<PixelStatus>& os,
                   PNG& img,
                   colorPicker& fillColor);

//     /*
//      * effects: returns true if given pixel is within the boundary
//      *          of the given image;
//      *          false otherwise.
//      */
//     bool isWithinImage(int x, int y, PNG& img);

//     /*
//      * requires: given pixel is within boudary of given image
//      * effects: returns true if given pixel is within fill region,
//      *          as indicated by the center point and tolerence;
//      *          returns false otherwise.
//      */
//     bool isWithinFillRegion(int x, int y, int ctr_x, int ctr_y,
//                             vector<vector<PixelStatus>>& imgMatrix, double tolerance);

    bool isWithinBounds(int x, int y, int ctr_x, int ctr_y,
                        vector<vector<PixelStatus>>& imgMatrix, double tolerance,PNG& img);

    /*
     * Adds a new frame to given animation if fillCount overflows.
     * Resets fillCount to 0 after an overflow.
     * @param: animation animation in which a new frame may be added
     * @param: img image after last fill
     * @param: fillCount number of pixels actually filled since last frame
     * @param: frameFreq frame frequency, requires this > 0
     */
    void addFrameToAnimation(animation& animation, PNG& img, int& fillCount, int frameFreq);

}
#include "filler.cpp"
#endif
