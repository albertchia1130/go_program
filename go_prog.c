#include <stdio.h>
#define X_AXIS 3
#define Y_AXIS 3

enum interState{
	empty =0,
	black,
        white
};
struct stone{
	enum interState stone_state;
	int x_axis;
	int y_axis;
	struct group *nextStone; //pointer to indicate which group this stone belongs too
    int StoneLiberty; //0-4 
};

struct group{
	struct stone *groupStartingStone;
	struct group *nextGroup;

};

_Bool white_turn = 1;
void draw();
enum interState Board_state[X_AXIS][Y_AXIS];
void main()
{
	int x,y;
	while(1)
	{
	   if (white_turn)
        {
	       printf("white turn:\n");
	       printf("x_axis:\n");
	       scanf("%d",&x);
	       printf("y_axis:\n");
	       scanf("%d",&y);
	       if(Board_state[x][y]== empty)
	       {
	         Board_state[x][y] = white;
	         
    		 white_turn = 0;
	       }else{
                 printf("invalid move\n");
	       }
	   }
	   else
       {
            printf("black turn\n");
            printf("x_axis:\n");
		    scanf("%d",&x);
		    printf("y_axis:\n");
	     	scanf("%d",&y);
           if(Board_state[x][y] == empty)
	       {
	    	  	Board_state[x][y] = black;
	    	  	
	        	 white_turn = 1;	
	    	}else{
	     	  printf("invalid move\n");
		   }
        } 
	   	draw();
    }
}

void draw()
{
       for(int x =0;x < X_AXIS;x++)
       {
	       for(int y = 0;y<Y_AXIS;y++)
	       {
                    if(Board_state[x][y] == empty)
			    printf(" 0 ");
		    else if(Board_state[x][y] == black)
			    printf(" b ");
		    else if(Board_state[x][y] == white)
			    printf(" w ");
	       }
       		printf("\n\n");
       }
}
