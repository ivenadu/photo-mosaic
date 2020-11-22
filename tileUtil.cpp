
// File:        tileUtil.cpp
// Author:      Cinda
// Date:        2020-10-31
// Description: file handling functions that prepare data for the tiling algorithm


#include "tileUtil.h"

/**
 * Function tile:
 * @param PNG & target: an image to use as base for the mosaic. it's pixels will be
 *                      be replaced by thumbnail images whose average color is close
 *                      to the pixel.
 * @param rgbtree & ss: a kd-tree of RGBAPixels, used as a query structure for
 *                      nearest neighbor search. 
 * @param map<RGBAPixel, string> & photos: a map that takes a color key and returns the
 *                      filename of an image whose average color is that key.
 *
 * returns: a PNG whose dimensions are TILESIZE times that of the target. Each
 * pixel in the target is used as a query to ss.findNearestNeighbor, and the response
 * is used as a key in photos. 
 */

PNG tiler::tile(PNG & target, const rgbtree & ss, map<RGBAPixel,string> & photos){

/* your code here! */

}

/* buildMap: function for building the map of <key, value> pairs, where the key is an
 * RGBAPixel representing the average color over an image, and the value is 
 * a string representing the path/filename.png of the TILESIZExTILESIZE image
 * whose average color is the key.
 * 
 * We've provided a bit of the C++ code that allows you to iterate over the files
 * in a directory. It is up to you to figure out what it means, and how to use it.
 * 
 * @param path is the subdirectory in which the tiles can be found. In our examples
 * this is imlib.
 *
*/
map<RGBAPixel, string> tiler::buildMap(string path) {

    map < RGBAPixel, string> thumbs;
    for (const auto & entry : fs::directory_iterator(path)) {
        PNG curr; curr.readFromFile(entry.path());
        unsigned int sum_r = 0;
        unsigned int sum_g = 0;
        unsigned int sum_b = 0;
        unsigned int sum_a = 0;
        int W = curr.width();
        int H = curr.height();
        
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                auto& p = *curr.getPixel(i,j);
                sum_r += p.r;
                sum_g += p.g;
                sum_b += p.r;
                sum_a += p.a;
            }
        }

        int total = W*H;
        sum_r /= total;
        sum_g /= total;
        sum_b /= total;
        sum_a /= total;

        thumbs.insert(std::make_pair(RGBAPixel(sum_r, sum_g, sum_b, sum_a), entry.path().string()));
    }

    return thumbs;
}


