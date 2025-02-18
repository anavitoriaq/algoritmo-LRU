#include <stdio.h>
#include <limits.h>

#define FRAME_COUNT 3  
#define PAGE_COUNT 10 

typedef struct {
    int page;     
    long timestamp; 
} PageFrame;

int findPage(PageFrame frames[], int page) {
    for (int i = 0; i < FRAME_COUNT; i++) {
        if (frames[i].page == page) {
            return i; 
        }
    }
    return -1; 
}

int findLRU(PageFrame frames[]) {
    int minIndex = 0;
    long minTime = frames[0].timestamp;
    
    for (int i = 1; i < FRAME_COUNT; i++) {
        if (frames[i].timestamp < minTime) {
            minTime = frames[i].timestamp;
            minIndex = i;
        }
    }
    return minIndex; 
}

int main() {
    int pages[PAGE_COUNT] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1};
    PageFrame frames[FRAME_COUNT]; 
    int time = 0, pageFaults = 0;

    for (int i = 0; i < FRAME_COUNT; i++) {
        frames[i].page = -1; 
        frames[i].timestamp = 0;
    }

    for (int i = 0; i < PAGE_COUNT; i++) {
        int page = pages[i];
        int index = findPage(frames, page);

        if (index != -1) {
            frames[index].timestamp = time;
        } else {
            int replaceIndex = findLRU(frames);
            frames[replaceIndex].page = page;
            frames[replaceIndex].timestamp = time;
            pageFaults++;
        }

        time++; 

        printf("Passo %d - Página %d referenciada | Frames: ", i + 1, page);
        for (int j = 0; j < FRAME_COUNT; j++) {
            printf("[%d] ", frames[j].page);
        }
        printf("\n");
    }

    printf("\nTotal de Page Faults: %d\n", pageFaults);
    return 0;
}