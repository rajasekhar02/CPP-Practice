#include <stdio.h>
#include <stdlib.h>
#define DIFFLIST(A)  \
    A(EASY, Easy, e) \
    A(HARD, Hard, h)
// refer to https://en.cppreference.com/w/c/preprocessor/replace
#define ENUM(upper, title, lower) DIFF_##upper,
#define TITLE(upper, title, lower) #title,
#define ENCODE(upper, title, lower) #lower
#define CONFIG(upper, title, lower) ":" #title
static char const *const slant_diffnames[] = {DIFFLIST(TITLE)};
static char const slant_diffchars[] = DIFFLIST(ENCODE);
#define DIFFCONFIG DIFFLIST(CONFIG)
enum
{
    DIFFLIST(ENUM) DIFFCOUNT
};
struct solver
{
    int x;
};

typedef struct
{
    int x, y, z;
} game_clues;

struct solver *new_solver(int w, int h)
{
    struct solver *y = (struct solver *)malloc(sizeof(struct solver));
    y->x = 19;
    return y;
}
/**
 * @brief Structure Copying
 *
 * Only applicable to structure without properties of pointer type
 *
 */
game_clues *structureCopy(const game_clues *y)
{
    game_clues *new = (game_clues *)malloc(sizeof(game_clues));
    *new = *y;
    return new;
}
int main()
{
    // declaration of structure without using typedef
    struct solver *z = new_solver(10, 11);
    game_clues y;
    y.x = 10;
    y.y = 100;
    y.z = 10;
    game_clues *yCopy = structureCopy(&y);
    yCopy->x = 11;
    printf("Structure Copying Output: %d %d\n", y.x, yCopy->x);
    printf("%d %d\n", z->x, y.x);
    char *choicenames = DIFFCONFIG;
    printf("Preprocessors Output: %s", choicenames);
    // to see the effect of preprocessor use -E option in compilation eg: gcc -e <file_name>.c
    printf("Preprocessors Output: %d %d %d", DIFFLIST(ENUM) 12);
    return 0;
}
/**
 * Static Functions in C
 *
 * static functions are functions that are only visible to other functions in the same file
 *
 */
