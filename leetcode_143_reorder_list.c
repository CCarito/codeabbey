#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

void reorderList(struct ListNode* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL)
        return;
    
    // Find the middle of the list
    struct ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Reverse the second half of the list
    struct ListNode *prev = NULL, *curr = slow->next, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    slow->next = NULL;
    
    // Merge the two halves
    struct ListNode *first = head, *second = prev;
    while (second) {
        struct ListNode *first_next = first->next;
        struct ListNode *second_next = second->next;
        first->next = second;
        second->next = first_next;
        first = first_next;
        second = second_next;
    }
}

// Utility function to create a new node
struct ListNode* newNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// Utility function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // Create a sample linked list
    struct ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    
    printf("Original list: ");
    printList(head);
    
    reorderList(head);
    
    printf("Reordered list: ");
    printList(head);
    
    return 0;
}
