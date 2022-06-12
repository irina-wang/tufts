#include "pnmdiff.h"
#include "stdlib.h"

/* 纯属测试用的，可以写进readme里 */
int main(int argc, char **argv) {
    if (argc != 3) exit(EXIT_FAILURE);
    FILE *file1 = fopen(argv[1], "r"), *file2 = fopen(argv[2], "r");
    Pnmrdr_T img1 = Pnmrdr_new(file1);
    Pnmrdr_T img2 = Pnmrdr_new(file2);
    compare_pnm(img1, img2);
    fclose(file1);
    fclose(file2);
    Pnmrdr_free(&img1);
    Pnmrdr_free(&img2);
}

void compare_pnm(Pnmrdr_T img1, Pnmrdr_T img2) {
    printf("1st Img Type: P%d\n2nd Img Type: P%d\n", 
           Pnmrdr_data(img1).type, Pnmrdr_data(img2).type);
    if (Pnmrdr_data(img1).height != Pnmrdr_data(img2).height ||
        Pnmrdr_data(img1).width != Pnmrdr_data(img2).width) {
        printf("Images have different sizes.\n");
        return;
    }
    int pixel_num = Pnmrdr_data(img1).width * Pnmrdr_data(img1).height, ct = 0,
        img1_p, img2_p;
    for (int i = 0; i < pixel_num; i++) {
        img1_p = Pnmrdr_get(img1);
        img2_p = Pnmrdr_get(img2);
        if (img1_p != img2_p) {
            //printf("Img1: %d    Img2: %d\n", img1_p, img2_p);
            ct++;
        }
    }
    printf("Total number of diff pixel: %d\n", ct);
}
