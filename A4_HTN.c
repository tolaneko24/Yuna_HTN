#include <stdio.h>
#include <stdlib.h>

//Ex1

/* Cấu trúc 1 node của linked list */
struct node {
    int data;
    struct node* next;
};

/* Hàm cấp phát 1 node mới
   Trả về con trỏ đến node mới, hoặc NULL nếu malloc thất bại */
struct node* nalloc(int data) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p != NULL) {
        p->data = data;
        p->next = NULL;
    }
    return p;
}

/* (a) Hiển thị toàn bộ phần tử trong list */
void display(struct node* head) {
    struct node* p = head;

    printf("[");
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(" -> ");
        }
        p = p->next;
    }
    printf("]\n");
}

/* (b) Thêm phần tử vào cuối list
   Trả về head mới của list */
struct node* addback(struct node* head, int data) {
    struct node* newnode = nalloc(data);
    struct node* p;

    /* Nếu cấp phát thất bại thì giữ nguyên list cũ */
    if (newnode == NULL) {
        printf("Memory allocation failed when adding %d\n", data);
        return head;
    }

    /* Nếu list rỗng, node mới chính là head */
    if (head == NULL) {
        return newnode;
    }

    /* Duyệt đến node cuối cùng */
    p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    /* Nối node mới vào cuối */
    p->next = newnode;
    return head;
}

/* (c) Tìm phần tử có giá trị data
   Trả về con trỏ đến node tìm thấy, hoặc NULL nếu không có */
struct node* find(struct node* head, int data) {
    struct node* p = head;

    while (p != NULL) {
        if (p->data == data) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

/* (d) Xóa node mà pelement trỏ tới
   Trả về head mới của list
   Chú ý xử lý cả trường hợp xóa head */
struct node* delnode(struct node* head, struct node* pelement) {
    struct node* p;

    /* Nếu list rỗng hoặc pelement không hợp lệ */
    if (head == NULL || pelement == NULL) {
        return head;
    }

    /* Trường hợp xóa head */
    if (head == pelement) {
        struct node* newhead = head->next;
        free(head);
        return newhead;
    }

    /* Tìm node đứng ngay trước pelement */
    p = head;
    while (p != NULL && p->next != pelement) {
        p = p->next;
    }

    /* Nếu không tìm thấy pelement trong list, không làm gì */
    if (p == NULL) {
        return head;
    }

    /* Bỏ qua pelement rồi giải phóng nó */
    p->next = pelement->next;
    free(pelement);

    return head;
}

/* (e) Xóa toàn bộ list
   Sau khi free từng node thì không dùng lại node đó nữa */
void freelist(struct node* head) {
    struct node* p = head;
    struct node* nextnode;

    while (p != NULL) {
        nextnode = p->next; /* lưu node kế tiếp trước khi free */
        free(p);
        p = nextnode;
    }
}

/*Ex2*/

/* Cấu trúc 1 node của cây nhị phân */
struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
};

/* (a) Cấp phát node mới cho cây */
struct tnode* talloc(int data) {
    struct tnode* p = (struct tnode*)malloc(sizeof(struct tnode));
    if (p != NULL) {
        p->data = data;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

/* (b) Chèn node vào binary search tree
   Quy tắc:
   - nhỏ hơn root thì sang trái
   - lớn hơn hoặc bằng thì sang phải
   Trả về root mới */
struct tnode* addnode(struct tnode* root, int data) {
    if (root == NULL) {
        return talloc(data);
    }

    if (data < root->data) {
        root->left = addnode(root->left, data);
    } else {
        root->right = addnode(root->right, data);
    }

    return root;
}

/* (c) Duyệt pre-order: root -> left -> right */
void preorder(struct tnode* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

/* (d) Duyệt in-order: left -> root -> right
   Với BST thì kết quả sẽ được sắp tăng dần */
void inorder(struct tnode* root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* (e) Xóa toàn bộ cây theo post-order
   left -> right -> root
   Hàm trả về số node đã xóa */
int deltree(struct tnode* root) {
    int count_left, count_right;

    if (root == NULL) {
        return 0;
    }

    count_left = deltree(root->left);
    count_right = deltree(root->right);

    free(root);
    return count_left + count_right + 1;
}

/* =========================================================
   TEST CODE
   ========================================================= */

int main(void) {
    /* -----------------------------
       TEST EXERCISE 1 - LINKED LIST
       ----------------------------- */
    struct node* head = NULL;
    struct node* p;

    printf("Ex1:\n");

    /* Thêm các phần tử vào cuối list */
    head = addback(head, 10);
    head = addback(head, 20);
    head = addback(head, 30);
    head = addback(head, 40);

    printf("Initial list: ");
    display(head);

    /* Tìm một phần tử tồn tại */
    p = find(head, 30);
    if (p != NULL) {
        printf("Found element with data = %d\n", p->data);
    } else {
        printf("Element 30 not found\n");
    }

    /* Tìm một phần tử không tồn tại */
    p = find(head, 99);
    if (p != NULL) {
        printf("Found element with data = %d\n", p->data);
    } else {
        printf("Element 99 not found\n");
    }

    /* Xóa một node ở giữa (node có data = 30) */
    p = find(head, 30);
    head = delnode(head, p);
    printf("After deleting 30: ");
    display(head);

    /* Xóa head (node có data = 10) */
    p = find(head, 10);
    head = delnode(head, p);
    printf("After deleting head (10): ");
    display(head);

    /* Thử xóa phần tử không tồn tại */
    p = find(head, 999);
    head = delnode(head, p); /* p = NULL, list giữ nguyên */
    printf("After trying to delete 999: ");
    display(head);

    /* Giải phóng toàn bộ list */
    freelist(head);
    head = NULL; /* tránh dùng lại con trỏ cũ */

    printf("After freeing list: ");
    display(head);

    printf("\n");

    /* -----------------------------
       TEST EXERCISE 2 - BINARY TREE
       ----------------------------- */
    struct tnode* root = NULL;
    int deleted_count;

    printf("Ex2:\n");

    /* Chèn theo đúng thứ tự đề bài yêu cầu:
       3, 1, 0, 2, 8, 6, 5, 9 */
    root = addnode(root, 3);
    root = addnode(root, 1);
    root = addnode(root, 0);
    root = addnode(root, 2);
    root = addnode(root, 8);
    root = addnode(root, 6);
    root = addnode(root, 5);
    root = addnode(root, 9);

    printf("Pre-order traversal: ");
    preorder(root);
    printf("\n");

    printf("In-order traversal: ");
    inorder(root);
    printf("\n");

    deleted_count = deltree(root);
    root = NULL; /* tránh dùng lại con trỏ đã free */

    printf("Number of deleted nodes: %d\n", deleted_count);

    return 0;
}
