#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <string>

using std::string;
extern "C"
{
    void drawPolynomialAsm(float imgWidth, float imgHeight, float a, float b, float c, float d, float S, unsigned int *pixels);
}

void drawPolynomial(float imgWidth, float imgHeight, float a, float b, float c, float d, float S, unsigned int *pixels)
{
    //for(int x=0;x<imgWidth;x++)
//    float x = 0;
  //  float y = x * x * x * a + x * x * b + x * c + d;
    //float dx = sqrt(S-dy*dy);
   // float dx = sqrt((S*S) / ((3 * x * x * a + 2 * x * b + c) * (3 * x * x * a + 2 * x * b + c) + 1));
    //S= dx2+dy2
    //S= dx2 +dx2*(6*x+2*b)
    //float dx2=S/(6*x+2*b+1);
    //y=x^3

    //float dy = (3 * x * x * a + 2 * x * b + c) * dx;
    float dy,dx,x,y;
    //float dx=sqrt(S);
    //float dy2 = 6 *x +2*b *dx2;
    //float dx=sqrt(dx2);
    //dx=0.1;
    //dy=0.1;
    // float dy=sqrt(dy2);
    //float dy1 =S-dx*dx;
    //float dy = sqrt(S-dx*dx);
    //float x2;
    //float y2;
    //draw  first point
    x=0;
    y=d;
int i = (x*imgWidth)/100;
    int j = (y*imgHeight)/100;
    

    int index  = ((imgHeight - j)*imgHeight + i )- imgWidth ;
    //int index=0;
    //int index =1000000;
    //	while (index<1000000)
   // pixels[1020000]=0;
   //x+=dx;
   
    for (x=0; i < 1000 && j < 1000; x +=0)
    {

        // index =y*1000 - x;
        //i++;
//y = x * x * x * a + x * x * b + x * c + d;
       
        //if(x > imgWidth && y >imgHeight)break;

        //pixels[index] = 0xFF000000;
        

        //x+=dx;
        //y+=dy;
        //dy = (3*x*x*a+2*x*b+c);
        //dx=(S-dy*dy);
        //std::cout<<" dx= "<<dx<<" dy= "<<dy<<std::endl;
        //x+=0.001; //one pixel is 0.1

        //x = x + dx;
        //y = y + dy;
        // x+=0.1;

        //i = x / 1000;
        //j = y / 1000;
       
       // index = (imgHeight*j)+i;
        dx = sqrt((S*S) / ((3 * x * x * a + 2 * x * b + c) * (3 * x * x * a + 2 * x * b + c) + 1));

        
        dy = (3 * x * x * a + 2 * x * b + c) * dx;
        
         i=x*imgWidth/100;
        j=y*imgHeight/100;
        index = index  = (imgHeight - j)*imgHeight + i - imgWidth ;
        x+=dx;
        y += dy;
        if(index>(imgHeight*imgWidth) ||i>1000||j>1000)return;

        pixels[index] = 0;
         if(i<300)
        {
            std::cout << "index " << index << std::endl;
            std::cout << "x=" << x << " y=" << y << " i=" << i << " j=" << j << " dx=" << dx << " dy=" << dy <<" dx^2+dy^2="<<dy*dy+dx*dx<<"?="<<S*S<< std::endl;
        }
        //dx=sqrt(S/((3*x*x*a+2*x*b+c)*(3*x*x*a+2*x*b+c)+1));
        //dy = (3*x*x*a+2*x*b+c)*dx;
        //SDL_RenderDrawLine(oldx,oldy,x,y)
    }
    std::cout << "end\n";
}


int main(int argc, char **argv)
{
    if (argc < 6)
    {
        std::cout << "Not enough arguments\n";
        std::cout << "Please give function parametrs (ax^3+bx^2+cx+d) and the jump value(dx^2+dy^2=S)" << argv[0] << " <a> <b> <c> <d> <S>\n";
        return 1;
    }
    unsigned int imageWidth = 1000, imageHeight = 1000;

    //imageWidth = atoi(argv[1]);
    //imageHeight = atoi(argv[2]);
    float a = atof(argv[1]);
    float b = atof(argv[2]);
    float c = atof(argv[3]);
    float d = atof(argv[4]);
    float S = atof(argv[5]);

    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("SDL2 polynomial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, imageWidth, imageHeight, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, imageWidth, imageHeight);
    
    
    unsigned int *pixels = new unsigned int[imageWidth*imageHeight];
   
    
    //srand(time(NULL));
    memset(pixels, 255, imageWidth * imageHeight * sizeof(unsigned int)); //set pixel array to white

//    drawPolynomial(imageWidth,imageHeight,a, b, c, d, S,pixels);
    drawPolynomialAsm(imageWidth, imageHeight, a, b, c, d, S, pixels);
    
    SDL_StartTextInput();
    char *text;
    
    int n = 0;
    bool error = false;
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, imageWidth * sizeof(Uint32));
        SDL_WaitEvent(&event);
        
        switch (event.type)
        {

            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_TAB)
                {
                    memset(pixels, 255, imageWidth * imageHeight * sizeof(Uint32)); //set pixel array to white
                    do
                    {
                        error=false;
                        char crChar;
                        float data;
                        std::cout << "Podaj nazwe argumentu do zmiany\n";
                         
                        std::cin >> crChar;
                         while((getchar()!='\n'));
                        std::cout << "Podaj nowa wartosc argumentu\n";
                        std::cin >> data;
                        while((getchar()!='\n'));
                        std::cout << crChar << "=" << data << std::endl;
                        switch (crChar)
                        {
                        case 'a':
                            a = data;
                           // error = false;
                            break;
                        case 'b':
                            b = data;
                            //error = false;
                            break;
                        case 'c':
                            c = data;
                            //error = false;
                            break;
                        case 'd':
                            d = data;
                            //error = false;
                            break;
                        case 's':
                            S = data;
                            //error = false;
                            break;
                        default:
                            std::cout << "blad \n";
                            error = true;
                            break;
                        }

                    } while (error);
                    drawPolynomialAsm(imageWidth, imageHeight, a, b, c, d, S, pixels);
                    std::cout << "Wartosc pomyslnie zmieniona\n";
                    break;
                }
                break;
            }
            
        case SDL_QUIT:
            quit = true;
            break;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_StopTextInput();
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
