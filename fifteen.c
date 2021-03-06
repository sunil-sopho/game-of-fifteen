/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9
#define CONS 0

// board
int board[DIM_MAX][DIM_MAX];
 int ac_x, ac_y, rp_x, rp_y;

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }
        else
        {
            board[rp_x][rp_y] = tile;
            board[ac_x][ac_y] = CONS;
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int siz = d * d - 1;
    if ( d % 2)
    {
        board[d - 1][d - 1] = CONS; 
        for(int i = 0;i < d;i++)
        {
            for(int j=0;j < d;j++)
            {
                if (siz != 0)
                {
                    board[i][j] = siz;
                    siz = siz - 1;
                }
            }
            
        }
    }
    
    else
    {
        board[d - 1][d - 1] = CONS;
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
        for(int i=0;i < d;i++)
        {
            for(int j=0;j < d;j++)
            {
                if (siz >= 3)
                {
                    board[i][j] = siz;
                    siz = siz - 1;
                }
            }
        }
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i=0;i < d;i++)
    {
        for(int j=0;j < d;j++)
        {
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
 // int ac_x,ac_y,rp_x,rp_y;
bool move(int tile)
{
    int i=0, j=0;
    
    for(i = 0;i < d;i++)
    {
        for(j = 0;j < d;j++)
        {
            if (board[i][j] == tile)
            {
                ac_x = i;
                ac_y = j;
                int aadd = -1, badd = -1;
                for(aadd = -1;aadd < 2;aadd++)
                {
                    for(badd = -1;badd < 2;badd++)
                    {
                        if ((aadd == -1 && badd == -1) || 
                        (aadd == -1 && badd == 1) || (aadd == 1 && badd == -1)
                        || (aadd == 1 && badd == 1))
                        {
                            continue;
                        }    
                        if ((i + aadd >= 0) && (i + aadd < d) && 
                        (j + badd >= 0) && (j + badd < d))
                        {
                            if (board[i + aadd][j + badd] == CONS)
                            {
                                rp_x = i + aadd;
                                rp_y = j + badd;
                                return true;
                            }    
                        }
                    }
                }
            }
        }
        printf("\n");
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{ 
    int ele = 1;
    
    for(int i=0;i < d;i++)
    {
        for(int j=0;j < d;j++)
        {
            if (i == d - 1 && j == d - 1)
            {
                break;
            }    
            if (board[i][j] != ele)
            {
                return false;
            }    
            ele++;
        }
    }
    return true;
}


