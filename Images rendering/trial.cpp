#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct QuadtreeNode
{
    int depth;
    Vec3b color;
    bool isLeaf;
    QuadtreeNode* children[4];
};

QuadtreeNode* createQuadtree(const vector<vector<Vec3b>>& image, int depthThreshold, double colorThreshold)
{
    int imageHeight = image.size();
    int imageWidth = image[0].size();

    QuadtreeNode* node = new QuadtreeNode();
    node->depth = 0;

    if (imageHeight == 1 && imageWidth == 1)
    {
        node->color = image[0][0];
        node->isLeaf = true;
        for (int i = 0; i < 4; ++i)
            node->children[i] = nullptr;
    }
    else if (node->depth >= depthThreshold)
    {
        int sumB = 0, sumG = 0, sumR = 0;

        for (int y = 0; y < imageHeight; ++y)
        {
            for (int x = 0; x < imageWidth; ++x)
            {
                sumB += image[y][x][0];
                sumG += image[y][x][1];
                sumR += image[y][x][2];
            }
        }

        int totalPixels = imageHeight * imageWidth;
        node->color[0] = static_cast<uchar>(sumB / totalPixels);
        node->color[1] = static_cast<uchar>(sumG / totalPixels);
        node->color[2] = static_cast<uchar>(sumR / totalPixels);
        node->isLeaf = true;
        for (int i = 0; i < 4; ++i)
            node->children[i] = nullptr;
    }
    else
    {
        node->isLeaf = false;
        int newDepth = node->depth + 1;
        int halfWidth = imageWidth / 2;
        int halfHeight = imageHeight / 2;

        vector<vector<Vec3b>> quadrant1(halfHeight, vector<Vec3b>(halfWidth));
        vector<vector<Vec3b>> quadrant2(halfHeight, vector<Vec3b>(halfWidth));
        vector<vector<Vec3b>> quadrant3(halfHeight, vector<Vec3b>(halfWidth));
        vector<vector<Vec3b>> quadrant4(halfHeight, vector<Vec3b>(halfWidth));

        for (int y = 0; y < halfHeight; ++y)
        {
            for (int x = 0; x < halfWidth; ++x)
            {
                quadrant1[y][x] = image[y][x];
                quadrant2[y][x] = image[y][x + halfWidth];
                quadrant3[y][x] = image[y + halfHeight][x];
                quadrant4[y][x] = image[y + halfHeight][x + halfWidth];
            }
        }

        node->children[0] = createQuadtree(quadrant1, depthThreshold, colorThreshold);
        node->children[1] = createQuadtree(quadrant2, depthThreshold, colorThreshold);
        node->children[2] = createQuadtree(quadrant3, depthThreshold, colorThreshold);
        node->children[3] = createQuadtree(quadrant4, depthThreshold, colorThreshold);
    }

    return node;
}

void destroyQuadtree(QuadtreeNode* node)
{
    if (node != nullptr)
    {
        if (!node->isLeaf)
        {
            for (int i = 0; i < 4; ++i)
                destroyQuadtree(node->children[i]);
        }

        delete node;
    }
}

int main()
{
    // Load the colored image
    string fileName = "colored_image.jpg";
    Mat image = imread(fileName);

    if (image.empty())
    {
        cerr << "Failed to load image: " << fileName << endl;
        return -1;
    }

    // Create a 3-channel 2D vector to store the image pixels
    int imageWidth = image.cols;
    int imageHeight = image.rows;

    vector<vector<Vec3b>> imageArray(imageHeight, vector<Vec3b>(imageWidth));

    // Store the image pixels in the vector
    for (int y = 0; y < imageHeight; ++y)
    {
        for (int x = 0; x < imageWidth; ++x)
        {
            Vec3b pixel = image.at<Vec3b>(y, x);
            imageArray[y][x] = pixel;
        }
    }

    // Create the Quadtree representation
    int depthThreshold = 7; // Maximum depth for termination
    //The depth threshold in the Quadtree fractal compression algorithm determines the maximum depth or level of the Quadtree. It limits the recursive subdivision of the image into quadrants.
    double colorThreshold = 5.0; // Color threshold for termination
    //The color threshold in the Quadtree fractal compression algorithm determines the maximum allowed color difference within a region before further subdivision is stopped 
    //It controls the level of color variation that is considered acceptable within a region of the image.
    QuadtreeNode* root = createQuadtree(imageArray, depthThreshold, colorThreshold);

    // Example usage: Traverse and print the Quadtree
    // This is just a simple example to illustrate the Quadtree structure
    // You can modify or extend it based on your specific requirements
    cout << "Quadtree representation:" << endl;

    function<void(QuadtreeNode*, int)> printQuadtree = [&](QuadtreeNode* node, int indent) {
        if (node != nullptr)
        {
            cout << string(indent, ' ') << "Depth: " << node->depth << ", Color: B=" << (int)node->color[0]
                 << " G=" << (int)node->color[1] << " R=" << (int)node->color[2] << endl;

            if (!node->isLeaf)
            {
                for (int i = 0; i < 4; ++i)
                    printQuadtree(node->children[i], indent + 2);
            }
        }
    };

    printQuadtree(root, 0);

    // Clean up the Quadtree
    destroyQuadtree(root);

    return 0;
}
