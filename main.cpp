#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>



void drawPolynomial(int imgWidth, int imgHeight,float a,float b,float c,float d,float S, Uint32 *pixels)
{
    //for(int x=0;x<imgWidth;x++)
	float x = 0;
	float y = x * x * x * a + x * x * b + x * c + d;
    //float dx = sqrt(S-dy*dy); 
    float dx=sqrt(S/((3*x*x*a+2*x*b+c)*(3*x*x*a+2*x*b+c)+1));
    //S= dx2+dy2
    //S= dx2 +dx2*(6*x+2*b)
    //float dx2=S/(6*x+2*b+1);
    //y=x^3
    
    float dy = (3*x*x*a+2*x*b+c)*dx;
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
	
    int j=0;
    int i=0;
    int index = (y*imgWidth-x);

//	while (index<1000000)
    for(x=0;i<1000&& j<1000;x+=dx)
	{

       // index =y*1000 - x;
        //i++;

     //if(i<0) 
     {

       std::cout<<i<<" "<<j<<" "<<dx<<" "<<dy<<std::endl;
      
        std::cout<<"index "<<index<<std::endl;
    }
        //if(x > imgWidth && y >imgHeight)break;
		 
		//pixels[index] = 0xFF000000;
        pixels[index]=0;
        
        //x+=dx;
        //y+=dy;
        //dy = (3*x*x*a+2*x*b+c);
         //dx=(S-dy*dy);
         //std::cout<<" dx= "<<dx<<" dy= "<<dy<<std::endl;
        //x+=0.001; //one pixel is 0.1
        
		//x = x + dx;
		//y = y + dy;
       // x+=0.1;
       
        i=x/dx;
        j=y/dx;
       index = (imgHeight-j)*imgWidth-(imgWidth-i);
       dx=sqrt(S/((3*x*x*a+2*x*b+c)*(3*x*x*a+2*x*b+c)+1));
        
        //y = x * x * x * a + x * x * b + x * c + d;
        y+=dy;
        dy = (3*x*x*a+2*x*b+c)*dx;
        //dx=sqrt(S/((3*x*x*a+2*x*b+c)*(3*x*x*a+2*x*b+c)+1));
        //dy = (3*x*x*a+2*x*b+c)*dx;
        //SDL_RenderDrawLine(oldx,oldy,x,y)
	}
    std::cout <<"end\n";
}

void drawSquare(Uint32 *pixels)
{
    for(int x=0,y=0;x<1000;x++,y++)
    {
        pixels[y*1000-x]=0;
    }
}


int main(int argc, char ** argv)
{
    if(argc < 6)
    {
		std::cout << "Not enough arguments\n";
        std::cout<<"Please give function parametrs (ax^3+bx^2+cx+d) and the jump value(dx^2+dy^2=S)"<<argv[0]<<" <a> <b> <c> <d> <S>\n";
        return 1;
    }
    int imageWidth=1000,imageHeight=1000;
   

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

    SDL_Window * window = SDL_CreateWindow("SDL2 polynomial",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, imageWidth, imageHeight, 0);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, imageWidth, imageHeight);
    
    Uint32 *pixels = new Uint32[imageWidth * imageHeight];
    srand(time(NULL));
    memset(pixels, 255, imageWidth * imageHeight * sizeof(Uint32)); //set pixel array to white
    

   
	drawPolynomial(imageWidth,imageHeight,a, b, c, d, S,pixels);

   
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, imageWidth * sizeof(Uint32));
        SDL_WaitEvent(&event);
		
	
		switch (event.type)
		{


		case SDL_QUIT:
			quit = true;
			break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
         
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
