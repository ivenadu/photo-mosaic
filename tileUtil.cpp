
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
    map<string, PNG> icons;

    int W = target.width();
    int H = target.height();

    PNG result;
    result.resize(W*TILESIZE, H*TILESIZE);

    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            const auto& query = *target.getPixel(i,j);
           // printf("[%d, %d]: query (%d, %d, %d)\n", i, j, query.r, query.g, query.b);
            const auto& near = ss.findNearestNeighbor(query);
           // printf("[%d, %d]: near (%d, %d, %d)\n", i, j, near.r, near.g, near.b);
            const auto& filename = photos[near];

            auto it = icons.find(filename);
            if(it == icons.end()){
                PNG img; img.readFromFile(filename);
                icons.insert(std::make_pair(filename, img));
            }
            const auto& icon = icons[filename];
            
            for(int r = 0; r < TILESIZE; r++){
                for(int c = 0; c < TILESIZE; c++){
                    //*result.getPixel(i*TILESIZE + r, j*TILESIZE + c) = *icon.getPixel(r,c);
                    auto t = result.getPixel(i*TILESIZE + r, j*TILESIZE + c);
                    auto s = icon.getPixel(r,c);
                    t->r = s->r;
                    t->g = s->g;
                    t->b = s->b;
                }
            }
        }
    }
    return result;
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
        int W = curr.width();
        int H = curr.height();

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                auto p = curr.getPixel(i,j);
                sum_r += p->r;
                sum_g += p->g;
                sum_b += p->b;
            }
        }

        int total = W*H;
        sum_r /= total;
        sum_g /= total;
        sum_b /= total;

        std::string filename = entry.path().string();
        thumbs.insert(std::make_pair(RGBAPixel(sum_r, sum_g, sum_b), filename));
    }

    return thumbs;
}


