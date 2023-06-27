#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    char* data;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
};

struct Node* createNewNode(const char* data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
    strcpy(node->data, data);
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void addingChild(struct Node* parent, struct Node* child) {
    child->parent = parent;
    if (parent->child == NULL) {
        parent->child = child;
    } else {
        struct Node* sibling = parent->child;
        while (sibling->sibling != NULL) {
            sibling = sibling->sibling;
        }
        sibling->sibling = child;
    }
}
struct Node* findingNode(struct Node* current, const char* code) {
    if (strcmp(current->data, code) == 0) {
        return current;
    }

    struct Node* result = NULL;
    struct Node* child = current->child;
    while (child != NULL) {
        result = findingNode(child, code);
        if (result != NULL) {
            break;
        }
        child = child->sibling;
    }

    return result;
}

struct Node* findLowestCommonAncestor(struct Node* node1, struct Node* node2) {
    struct Node* p1 = node1;
    struct Node* p2 = node2;

    int height1 = 0, height2 = 0;
    while (p1->parent != NULL) {
        height1++;
        p1 = p1->parent;
    }
    while (p2->parent != NULL) {
        height2++;
        p2 = p2->parent;
    }

    p1 = node1;
    p2 = node2;
    while (height1 > height2) {
        p1 = p1->parent;
        height1--;
    }
    while (height2 > height1) {
        p2 = p2->parent;
        height2--;
    }

    while (p1 != p2) {
        p1 = p1->parent;
        p2 = p2->parent;
    }
    return p1;
}

void printCommonLocations(struct Node* corp1, struct Node* corp2) {
    struct Node* common = findLowestCommonAncestor(corp1, corp2);
    printf("%s, %s -> ", corp1->data, corp2->data);
    while (common != NULL) {
        printf("%s, ", common->data);
        common = common->parent;
    }
    printf("\n");
}

int main() {

    struct Node* city = createNewNode("Bangalore");

    struct Node* suburbEast = createNewNode("Bangalore East");
    struct Node* suburbWest = createNewNode("Bangalore West");
    addingChild(city, suburbEast);
    addingChild(city, suburbWest);

    struct Node* townA = createNewNode("A");
    struct Node* townB = createNewNode("B");
    struct Node* townC = createNewNode("C");
    struct Node* townD = createNewNode("D");
    addingChild(suburbEast, townA);
    addingChild(suburbEast, townB);
    addingChild(suburbWest, townC);
    addingChild(suburbWest, townD);


    struct Node* corp1 =createNewNode("56001");
    struct Node* corp2 = createNewNode("56002");
    struct Node* corp3 = createNewNode("56003");
    struct Node* corp4 = createNewNode("56004");
    struct Node* corp5 = createNewNode("56005");
    struct Node* corp6 = createNewNode("56006");
    struct Node* corp7 = createNewNode("56007");
    struct Node* corp8 = createNewNode("56008");
    addingChild(townA, corp1);
    addingChild(townA, corp2);
    addingChild(townB, corp3);
    addingChild(townB, corp4);
    addingChild(townC, corp5);
    addingChild(townC, corp6);
    addingChild(townD, corp7);
    addingChild(townD, corp8);

    char code1[10], code2[10];
    printf("Enter the first corporation code : ");
    scanf("%s", code1);
    printf("Enter the second corporation code : ");
    scanf("%s", code2);

    struct Node* node1 = findingNode(city, code1);
    struct Node* node2 = findingNode(city, code2);

    if (node1 != NULL && node2 != NULL) {
        printCommonLocations(node1, node2);
    } else {
        printf("You have entered invalid corporation code.\n");
    }

    return 0;
}
