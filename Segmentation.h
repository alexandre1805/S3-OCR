void Segmentation(char *filename, int angle, int detection);
void vertical_Segmentation(int *array, int h, int w);
void horizontal_Segmentation(int *array, int h, int w);
void Block_Segmentation(int *array, int *res, int h, int w);
int find_size(int *res, int h, int w);
void find_coord(int *res, int *L, int *l, int *coord, int h, int w);
void create_line(int *array, int *car, int *coord, int L1, int *L, int *l, int nb, int h);
int detect_char(int *car, int L1, int *l, int *L, int nb);
void find_cuts(int *cut_coords,int *car,int L1, int *l, int *L, int nb);
