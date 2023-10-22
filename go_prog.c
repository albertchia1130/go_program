#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define X_AXIS 3
#define Y_AXIS 3

enum interState{
	empty =0,
	black,
    white
};

enum Direction{
	left =0,
	right,
	up,
	down,
	Not_applicable
};
struct stone{
	int x_position;
	int y_position;
	enum interState stone_state;
	struct group *BelongsTo; //pointer to indicate which group this stone belongs too
	struct stone *nextStone;
};

struct group{
	enum interState groupState;
	struct stone *LastStone;
	int GroupLiberty;
	struct group *nextGroup;
};

_Bool white_turn = 1;
struct group* HeadGroup;

void draw();
bool insertIntoGroup(int,int, enum Direction);
bool InsertStone(int,int,enum interState);
void CalculateGroupLiberty(enum interState);

struct stone Board_state[X_AXIS][Y_AXIS];


void main(){
	int x,y;
	while(1){
	   if (white_turn){
	       printf("white turn:\n");
	       printf("x_axis:\n");
	       scanf("%d",&x);
	       printf("y_axis:\n");
	       scanf("%d",&y);
	       if(InsertStone(x,y,white)){
    		  	white_turn = 0;
	       }
		   else{
                 printf("invalid move\n");
	       }
	   }
	   else{
            printf("black turn\n");
            printf("x_axis:\n");
		    scanf("%d",&x);
		    printf("y_axis:\n");
	     	scanf("%d",&y);
           if(InsertStone(x,y,black)){
	        	 white_turn = 1;	
	    	}
			else{
	     	  printf("invalid move\n");
		   }
        } 
		//system("clear");
	   	draw();
    }
}

// This function attempts to place the stone onto the board
bool InsertStone(int x, int y,enum interState State){ 
	bool ValidMove = true;
	// Return if the input is invalid (out of range or non empty)
	if(Board_state[x][y].stone_state != empty ||
	   (!((x>=0) && (x < X_AXIS)) ||  
	    !((x>=0) && (x < X_AXIS)))){
		return false;
	}
	Board_state[x][y].stone_state = State;
    
	if(x > 0 && Board_state[x-1][y].stone_state == State){
		ValidMove= insertIntoGroup(x,y,left);
		printf("left\n");
	}
	else if(x < (X_AXIS-1) && Board_state[x+1][y].stone_state == State){
		ValidMove= insertIntoGroup(x,y,right);
		printf("right\n");
	}
	else if(y > 0 && Board_state[x][y-1].stone_state == State){
        ValidMove= insertIntoGroup(x,y,down);
		printf("down\n");
	}
	else if(y  < (X_AXIS-1) && Board_state[x][y+1].stone_state == State){
		ValidMove= insertIntoGroup(x,y,up);
		printf("up\n");
	}
    else{
		ValidMove= insertIntoGroup(x,y,Not_applicable);
	}

	return ValidMove;

}

bool insertIntoGroup(int x,int y, enum Direction direc){
	if(direc == left){
		Board_state[x][y].BelongsTo = Board_state[x-1][y].BelongsTo;
		Board_state[x][y].nextStone = Board_state[x][y].BelongsTo->LastStone;
		Board_state[x][y].BelongsTo->LastStone == &Board_state[x][y];
	}
	else if(direc == right){
		Board_state[x][y].BelongsTo = Board_state[x+1][y].BelongsTo;
		Board_state[x][y].nextStone = Board_state[x][y].BelongsTo->LastStone;
		Board_state[x][y].BelongsTo->LastStone == &Board_state[x][y];
	}
	else if(direc == down){
		Board_state[x][y].BelongsTo = Board_state[x][y-1].BelongsTo;
		Board_state[x][y].nextStone = Board_state[x][y].BelongsTo->LastStone;
		Board_state[x][y].BelongsTo->LastStone == &Board_state[x][y];
	}
	else if(direc == up){
		Board_state[x][y].BelongsTo = Board_state[x][y+1].BelongsTo;
		Board_state[x][y].nextStone = Board_state[x][y].BelongsTo->LastStone;
		Board_state[x][y].BelongsTo->LastStone = &Board_state[x][y];
	}
	else if(direc == Not_applicable){
        Board_state[x][y].BelongsTo = (struct group*)malloc(sizeof(struct group));
		if(HeadGroup == NULL){
			HeadGroup = Board_state[x][y].BelongsTo;
		}
		else{
		    Board_state[x][y].BelongsTo->nextGroup = HeadGroup;
			HeadGroup = Board_state[x][y].BelongsTo;
		}
		Board_state[x][y].BelongsTo->LastStone = &Board_state[x][y];
        Board_state[x][y].BelongsTo->groupState = Board_state[x][y].stone_state;
	}
	Board_state[x][y].x_position = x;
	Board_state[x][y].y_position = y;
	CalculateGroupLiberty(Board_state[x][y].stone_state);
	return true;
}

void CalculateGroupLiberty(enum interState Priority){
	struct group *groupToCount;
	struct stone *stoneToCount;
	int x_count;
	int y_count;

	if(HeadGroup != NULL){
		groupToCount = HeadGroup;
	}
	else{
		return;
	}
	do{
		stoneToCount = groupToCount->LastStone;
		groupToCount->GroupLiberty =0;
		do{
			x_count = stoneToCount->x_position;
			y_count = stoneToCount->y_position;
			if(x_count > 0 && Board_state[x_count-1][y_count].stone_state == empty){
				groupToCount->GroupLiberty++;
			}
			else if(x_count < (X_AXIS-1) && Board_state[x_count+1][y_count].stone_state == empty){
				groupToCount->GroupLiberty++;
			}
			else if(y_count > 0 && Board_state[x_count][y_count-1].stone_state == empty){
 		       groupToCount->GroupLiberty++;
			}
			else if(y_count  < (X_AXIS-1) && Board_state[x_count][y_count+1].stone_state == empty){
				groupToCount->GroupLiberty++;
			}
			if(stoneToCount->nextStone !=NULL){
				stoneToCount= stoneToCount->nextStone;
			}
			else{
				break;
			}
			
		}while(true);

		//if(groupToCount->GroupLiberty == 0 && )


		if(groupToCount->nextGroup !=NULL){
			groupToCount= groupToCount->nextGroup;
		}
		else{
			break;
		}

	}while(true);

}


void draw(){
       for(int x =0;x < X_AXIS;x++){
	       for(int y = 0;y<Y_AXIS;y++){
           	 	if(Board_state[x][y].stone_state == empty)
			    	printf(" 0 ");
		    	else if(Board_state[x][y].stone_state == black)
			    	printf(" b ");
		    	else if(Board_state[x][y].stone_state == white)
			    	printf(" w ");
	       }
       		printf("\n\n");
       }
}
