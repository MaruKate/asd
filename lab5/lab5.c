#include<windows.h>
#include<math.h>
#include<stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <conio.h>
#define N 11
#define M_PI		3.14159265358979323846

double** randmm(int rows, int cols){
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix[i][j] =  (double)rand()/(double)(RAND_MAX/2.0);
        }
    }
    return matrix;
}

double** mulmr(double num, double **mat, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            mat[i][j] = mat[i][j] * num;
            if(mat[i][j] > 1.0){
                mat[i][j] = 1;
            }
            else mat[i][j] = 0;
        }
    }
    return mat;
}

void printMatrix(double **matrix, int rows, int cols){
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            printf("%g  ", matrix[i][j]);
        }
        printf("\n");
    }
}

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));
    return queue;
}


int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}


int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}


void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%d enqueued to queue\n", item);
}


int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}


int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}


int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабораторна робота 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow){
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

    hWnd=CreateWindow(ProgName,
                      "Лабораторна робота 5. Лавринович Марія",
                      WS_OVERLAPPEDWINDOW,
                      0,
                      0,
                      1080,
                      740,
                      (HWND)NULL,
                      (HMENU)NULL,
                      (HINSTANCE)hInstance,
                      (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)){
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                         WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;

    switch(messg)
    {
    case WM_PAINT :
        hdc=BeginPaint(hWnd, &ps);

        int n1 = 0;
        int n2 = 5;
        int n3 = 1;
        int n4 = 6;
        int n = 10 + n3;
        srand(0516);
        double** randomMatrix = randmm(n,n);
        double** matrix = mulmr((1.0 - n3*0.01 - n4*0.005 - 0.15), randomMatrix, n, n);

        printf("Adjacency matrix: \n");
        printMatrix(matrix, n, n);
        printf("\n");

        char *nn[13] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};
        int nx[15] = {};
        int ny[15] = {};
        int dx = 16, dy = 16, dtx = 5;
        int radius = 300;
        int offsetX = 500;
        int offsetY = 350;

        //Create coordinates
        float degree = (360/(n-1))*(M_PI/180);
        for(int i = 0; i<n; i++){
            nx[i] = offsetX + radius * cos(degree*i);
            ny[i] = offsetY + radius * sin(degree*i); //0.628319
        }

        //Center coordinates
        nx[n-1] = offsetX;
        ny[n-1] = offsetY;


        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN YPen = CreatePen(PS_SOLID, 2, RGB(255, 236, 66));
        HPEN GPen = CreatePen(PS_SOLID, 2, RGB(88, 235, 52));

        void arrow(float fi, int px, int py){
            px += dx*cos(fi);
            py += dx*sin(fi);
            int lx,ly,rx,ry;
            lx = px+dx*cos(fi+0.26);
            rx = px+dx*cos(fi-0.26);
            ly = py+dx*sin(fi+0.26);
            ry = py+dx*sin(fi-0.26);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
        }

        double getAngle(int nxi, int nyi, int nxj, int nyj){
            double angle = M_PI + acos((nxj-nxi)/(sqrt(pow((nxj-nxi),2)+pow((nyj-nyi),2))));
            if(nyj < nyi) angle *= -1;
            return angle;
        }

        void arrowPolyline(int fromX, int fromY, int toX, int toY){
            double angle = getAngle(fromX, fromY, toX, toY);
            arrow(angle, toX, toY);
        }

        void polyline(int nxi, int nyi, int nxj, int nyj){
            if((nxi > offsetX && nyi < offsetY) && (nxj < offsetX && nyj > offsetY)){ //I-III
                LineTo(hdc, offsetX+2*dx, offsetY+dy);
                LineTo(hdc, nxj, nyj);
                arrowPolyline(offsetX+2*dx, offsetY+dy,  nxj, nyj);
            } else if((nxi < offsetX && nyi > offsetY) && (nxj > offsetX && nyj < offsetY)){//III-I
                LineTo(hdc, offsetX-2*dx, offsetY-dy);
                LineTo(hdc, nxj-dx*0.2, nyj);
                arrowPolyline(offsetX-2*dx, offsetY-dy, nxj-dx*0.2, nyj);
            } else if((nxi > offsetX && nyi > offsetY) && (nxj < offsetX && nyj < offsetY)){//IV-II
                LineTo(hdc, offsetX+3*dx, offsetY);
                LineTo(hdc, nxj, nyj);
                arrowPolyline(offsetX+3*dx, offsetY,  nxj, nyj);
            } else if ((nxi < offsetX && nyi < offsetY) && (nxj > offsetX && nyj > offsetY)){//II-IV
                LineTo(hdc, offsetX-3*dx, offsetY-dy);
                LineTo(hdc, nxj, nyj);
                arrowPolyline(offsetX-3*dx, offsetY-dy,  nxj, nyj);
            } else if(nyi == offsetY){ //vertical vertices
                LineTo(hdc, offsetX, offsetY-2*dy);
                LineTo(hdc, nxj, nyj);
                arrowPolyline(offsetX, offsetY-2*dy, nxj, nyj);
            } else if(nyj == offsetY){ //vertical vertices
                LineTo(hdc, offsetX, offsetY+2*dy);
                LineTo(hdc, nxj, nyj);
            } else if(nxi == offsetX){ //horizontal vertices
                LineTo(hdc, offsetX-2*dx, offsetY);
                LineTo(hdc, nxj, nyj);
            } else if(nxj == offsetX){ //horizontal vertices
                LineTo(hdc, offsetX-4*dx, offsetY);
                LineTo(hdc, nxj-dx*0.3, nyj);
                arrowPolyline(offsetX-4*dx, offsetY, nxj-dx*0.3, nyj);
            }
        }

        void drawLoop(int nxi, int nyi, int nxj, int nyj){
            if(nyi > offsetY){
                Arc(hdc, nxj-5, nyj+5, nxj+40, nyj+50,    nxj, nyj, nxj, nyj);
                arrow(M_PI/1.8,nxj,nyj);
            } else {
                Arc(hdc, nxj+5, nyj-5, nxj-40, nyj-50,    nxj, nyj, nxj, nyj);
                arrow(-2.9,nxj,nyj-dy*0.05);
            }
        }

        void parallelLine(double angle, int nxi, int nyi, int nxj, int nyj){
            MoveToEx(hdc, nxi-dx*cos(angle-M_PI/16), nyi-dy*sin(angle-M_PI/16), NULL);
            LineTo(hdc, nxj+dx*cos(angle+M_PI/16), nyj+dy*sin(angle+M_PI/16));
            arrow(angle, (nxj+dx*cos(angle+M_PI/16))-16*cos(angle), (nyj+dy*sin(angle+M_PI/16))-16*sin(angle));
        }

        void drawVertex(HDC hdc, int* nx, int* ny, char* nn, int i) {
            Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
            TextOut(hdc, nx[i]-dtx,ny[i]-dy/2, nn[i], 2);
        }

        double** BFS_tree = (double**)malloc(N * sizeof(double*));
        for (int i = 0; i < N; i++){
            BFS_tree[i] = (double*)malloc(N * sizeof(double));
        }

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                BFS_tree[i][j] = 0;
            }
        }

        //BFS algorithm
        void BFS(double** adjMatrix, int startVertex){
            SelectObject(hdc, YPen);
            Ellipse(hdc, nx[startVertex]-dx, ny[startVertex]-dy, nx[startVertex]+dx, ny[startVertex]+dy);
            TextOut(hdc, nx[startVertex]-dtx, ny[startVertex]-dy/2, nn[startVertex], 2);
            char str[10];
            int counter;

            //Mark all vertices as not visited
            int verticesStatus[N];
            for(int i = 0; i < N; i++){
                verticesStatus[i] = 0;
            }

            //Mark starting vertex as visited
            verticesStatus[startVertex] = 1;

            struct Queue* queue = createQueue(N);
            //Enqueue starting vertex
            enqueue(queue, startVertex);

            //Set a counter in order to know in which order vertices were visited
            counter = 1;
            sprintf(str, "%d", counter);
            TextOut(hdc, nx[startVertex]+4*dtx,ny[startVertex]-dy/2, str, 2);

            while(queue->size != 0){
                //Get the first active vertex from the queue
                int currentVertex = dequeue(queue);
                printf("Visited %d\n", currentVertex+1);

                //Loop over adjacent vertices to the active vertex
                for(int i = 0; i < N; i++){
                    //If adjacent vertex is unvisited, then mark it as visited
                    if(adjMatrix[currentVertex][i] == 1 && verticesStatus[i] == 0){
                        //Add a connection to the BFS_tree matrix
                        BFS_tree[currentVertex][i] = 1;

                        //Delay for the drawing
                        sleep(1);
                        //system("pause");
                        //system("cls");
                        counter = counter + 1;

                        //Mark adjacent vertex as visited
                        verticesStatus[i] = counter;

                        //Add adjacent vertex to the end of the queue
                        enqueue(queue, i);

                        //Drawing vertices
                        if((currentVertex-i==(n-1)/2 || i-currentVertex==(n-1)/2) && currentVertex != n-1 && i != n-1 && n%2 == 1) {
                         MoveToEx(hdc, nx[currentVertex], ny[currentVertex], NULL);
                         polyline(nx[currentVertex], ny[currentVertex], nx[i], ny[i]);
                        } else {
                            double angle = getAngle(nx[currentVertex], ny[currentVertex], nx[i], ny[i]);
                            MoveToEx(hdc, nx[currentVertex], ny[currentVertex], NULL);
                            LineTo(hdc, nx[i], ny[i]);
                            arrow(angle, nx[i], ny[i]);
                        }
                        Ellipse(hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy);
                        TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 2);
                        Ellipse(hdc, nx[currentVertex]-dx, ny[currentVertex]-dy, nx[currentVertex]+dx, ny[currentVertex]+dy);
                        TextOut(hdc, nx[currentVertex]-dtx, ny[currentVertex]-dy/2, nn[currentVertex], 2);
                        sprintf(str, "%d", counter);
                        TextOut(hdc, nx[i]+4*dtx,ny[i]-dy+0.5, str, 2);
                    }
                }
            }

            //Print the order of visiting
            for(int i = 0; i < N; i++){
                printf("Vertex %d = %d\n", i+1, verticesStatus[i]);
            }
            printf("\n");
        }

        SelectObject(hdc, KPen);
        //BFS(matrix, 0);

        //Draw graph
        for(int i = 0; i<n; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 1){
                    if(i == j){
                         drawLoop(nx[i], ny[i], nx[j], ny[j]);
                    } else if((i-j==(n-1)/2 || j-i==(n-1)/2) && i != n-1 && j != n-1 && n%2 == 1) {
                         MoveToEx(hdc, nx[i], ny[i], NULL);
                         polyline(nx[i], ny[i], nx[j], ny[j]);
                    } else if(matrix[i][j] == matrix[j][i]){
                        double angle = getAngle(nx[i], ny[i], nx[j], ny[j]);
                        parallelLine(angle, nx[i], ny[i], nx[j], ny[j]);

                    } else {
                         double angle = getAngle(nx[i], ny[i], nx[j], ny[j]);
                         MoveToEx(hdc, nx[i], ny[i], NULL);
                         LineTo(hdc, nx[j], ny[j]);
                         arrow(angle, nx[j], ny[j]);
                    }
                }
            }
        }

        //Draw vertices
        SelectObject(hdc, BPen);
        for(int i = 0; i<n; i++){
            Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
            TextOut(hdc, nx[i]-dtx,ny[i]-dy/2, nn[i], 2);
        }

        //BFS call
        BFS(matrix, 0);
        printf("BFS tree matrix: \n");
        printMatrix(BFS_tree, n, n);

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
