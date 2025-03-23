#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Struktur Stack untuk Konversi Bilangan Desimal ke Biner
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
int isEmptyStack(Stack *s) { return s->top == -1; }
int isFullStack(Stack *s) { return s->top == MAX - 1; }
void push(Stack *s, int value) { if (!isFullStack(s)) s->data[++(s->top)] = value; }
int pop(Stack *s) { return !isEmptyStack(s) ? s->data[(s->top)--] : -1; }
void decimalToBinary(int n) {
    if (n == 0) {
        printf("0\n");
        return;
    }
    Stack s; initStack(&s);
    while (n > 0) { push(&s, n % 2); n /= 2; }
    while (!isEmptyStack(&s)) printf("%d", pop(&s));
    printf("\n");
}

// Struktur Queue untuk Simulasi Antrian Bank
typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = -1; }
int isEmptyQueue(Queue *q) { return q->front == -1; }
int isFullQueue(Queue *q) { return q->rear == MAX - 1; }
void enqueue(Queue *q, int value) { if (!isFullQueue(q)) { if (isEmptyQueue(q)) q->front = 0; q->data[++(q->rear)] = value; } }
int dequeue(Queue *q) { if (!isEmptyQueue(q)) { int value = q->data[q->front]; if (q->front == q->rear) initQueue(q); else q->front++; return value; } return -1; }
void printQueue(Queue *q) { if (!isEmptyQueue(q)) { for (int i = q->front; i <= q->rear; i++) printf("%d ", q->data[i]); printf("\n"); } else printf("Antrian kosong\n"); }

// Struktur Single Linked List untuk Data Pelanggan
typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

void insertCustomer(Node** head, int id) {
    Node* newNode = createNode(id);
    newNode->next = *head;
    *head = newNode;
}

void displayCustomers(Node* head) {
    while (head) { printf("Pelanggan %d\n", head->id); head = head->next; }
}

int main() {
    int choice, num, counter = 1;
    Queue q; Stack s; Node* customers = NULL;
    initQueue(&q); initStack(&s);
    
    while (1) {
        printf("\nMenu:\n1. Konversi Desimal ke Biner\n2. Ambil Antrian\n3. Proses Antrian\n4. Cetak Antrian\n5. Tambah Data Pelanggan\n6. Tampilkan Data Pelanggan\n7. Keluar\nPilihan: ");
        if (scanf("%d", &choice) != 1) {
            printf("Input tidak valid! Harap masukkan angka.\n");
            while (getchar() != '\n'); // Membersihkan buffer input
            continue;
        }

        switch (choice) {
            case 1:
                printf("Masukkan bilangan desimal: ");
                if (scanf("%d", &num) != 1 || num < 0) {
                    printf("Input tidak valid! Harap masukkan bilangan bulat positif.\n");
                    while (getchar() != '\n'); // Membersihkan buffer input
                    continue;
                }
                while (getchar() != '\n'); // Pastikan buffer bersih setelah input
                printf("Biner: "); decimalToBinary(num);
                break;
            case 2:
                enqueue(&q, counter++);
                printf("Nomor antrian diambil!\n"); printQueue(&q);
                break;
            case 3:
                if (!isEmptyQueue(&q)) printf("Nomor antrian %d diproses\n", dequeue(&q));
                else printf("Tidak ada antrian\n");
                printQueue(&q);
                break;
            case 4:
                printQueue(&q);
                break;
            case 5:
                printf("Masukkan ID pelanggan: ");
                if (scanf("%d", &num) != 1 || num < 0) {
                    printf("Input tidak valid! Harap masukkan bilangan bulat positif.\n");
                    while (getchar() != '\n'); // Membersihkan buffer input
                    continue;
                }
                while (getchar() != '\n'); // Pastikan buffer bersih setelah input
                insertCustomer(&customers, num);
                printf("Data pelanggan ditambahkan!\n");
                break;
            case 6:
                printf("Daftar Pelanggan:\n");
                displayCustomers(customers);
                break;
            case 7:
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}