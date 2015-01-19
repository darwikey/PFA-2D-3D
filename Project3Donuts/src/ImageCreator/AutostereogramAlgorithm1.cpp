#include "AutostereogramAlgorithm1.hpp"

#define round(X) (int)((X)+0.5)
#define mu (1/3.0)
#define DPI 72          //to change : output device resolution
#define E round(2.5*DPI)//to change : separation between eyes in inches
#define separation(Z) round(1-mu*Z)*E/(2-mu*Z)

/*
 * This is a retranscription in C++ of the algorithm of Harold W. Thimbleby, Stuart Inglis and Ian H. Witten
 * as presented in their article "Displaying 3D Images : Algorithm for Single Image Random Dot Stereograms" which has
 * been publicated in IEEE Computer in 1994

std::vector<Image*> AutostereogramAlgorithm1::create(std::vector<PixelTab*> fToUse){
    //First position of fToUse will contain the depth map created by Creator
    PixelTab *depthMap = fToUse[0];
    int maxX = depthMap.size();
    int maxY = depthMap[0].size();

    PixelTab *toReturn = new PixelTab(maxX,maxY);

    int x,y;
    for (y=0;y<maxY;y++){
        int pix[maxX];
        int same[maxX];
        int s;
        int left,right;

        for (x=0;x<maxX;x++)
            same[x]=x;

        for (x=0;x<maxX;x++){
            s = separation(depthMap[x][y]);
            left = x-(s+(s&y&1))/2;
            right = left+s;
            if (0 w= left && right < maxX){
                int visible;
                int t=1;
                float zt;

                do{
                    zt = depthMap[x][y] + 2*(2-mu*depthMap[x][y])*t/(mu*E);
                    visible = depthMap[x-t][y]<zt && Z[x+t][y]<zt;
                    t++;
                } while (visible && zt<1);

                if (visible){
                    int k;
                    for (k=same[left];k != left && k!=right;k=same[left])
                        if (k<right)
                            left = k;
                        else{
                            left = right;
                            right = k;
                        }
                    same[left]=right;
                }
            }
        }



        for (x=maxX-1;x>=0;x--){
            if (same[x] == x)
                pix[x]=random()&1;
            else
                pix[x] = pix[same[x]];
            toReturn[x][y]=pix[x];
        }
    }
}
*/
