#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
char* url;
struct Node* prev;
struct Node* next;
} Node;
typedef struct BrowserHistory {
Node* current;
Node* bookmark;
} BrowserHistory;
Node* createNode(char* url) {
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->url = strdup(url);
newNode->prev = NULL;
newNode->next = NULL;
return newNode;
}
BrowserHistory* initializeBrowserHistory(char* homepage) {
BrowserHistory* history =
(BrowserHistory*)malloc(sizeof(BrowserHistory));
history->current = createNode(homepage);
history->bookmark = NULL;
return history;
}
void visit(BrowserHistory* history, char* url) {
Node* newNode = createNode(url);
newNode->prev = history->current;
history->current->next = newNode;
history->current = newNode;
while (history->current->next != NULL) {
free(history->current->next->url);
Node* temp = history->current->next;
history->current->next = temp->next;
free(temp);
}
}
char* goBack(BrowserHistory* history, int steps) {
while (steps > 0 && history->current->prev != NULL) {
history->current = history->current->prev;
steps--;
}
return history->current->url;
}
char* goForward(BrowserHistory* history, int steps) {
while (steps > 0 && history->current->next != NULL) {
history->current = history->current->next;
steps--;
}
return history->current->url;
}
void bookmarkCurrent(BrowserHistory* history) {
history->bookmark = history->current;
}
char* goToBookmark(BrowserHistory* history) {
if (history->bookmark != NULL) {
history->current = history->bookmark;
return history->current->url;
} else {
return "No bookmark set.";
}
}
void freeBrowserHistory(BrowserHistory* history) {
Node* current = history->current;
while (current != NULL) {
Node* temp = current;
current = current->prev;
free(temp->url);
free(temp);
}
free(history);
}
void displayHistory(BrowserHistory* history) {
Node* currentNode = history->current;
printf("\nBrowser History:\n");
while (currentNode != NULL) {
printf("%s\n", currentNode->url);
currentNode = currentNode->prev;
}
}
void printMenu() {
printf("\nMenu:\n");
printf("1. Visit a URL\n");
printf("2. Go back\n");
printf("3. Go forward\n");
printf("4. Bookmark current URL\n");
printf("5. Go to bookmark\n");
printf("6.display\n");
printf("7. Exit\n");
}
int main() {
char* homepage = "example.com";
BrowserHistory* history = initializeBrowserHistory(homepage);
int choice;
do {
printMenu();
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
{
char url[100];
printf("Enter the URL to visit: ");
scanf("%s", url);
visit(history, url);
printf("Visited: %s\n", url);
}
break;
case 2:
{
int steps;
printf("Enter the number of steps to go back: ");
scanf("%d", &steps);
printf("Current URL after going back: %s\n",
goBack(history, steps));
}
break;
case 3:
{
int steps;
printf("Enter the number of steps to go forward: ");
scanf("%d", &steps);
printf("Current URL after going forward: %s\n",
goForward(history, steps));
}
break;
case 4:
bookmarkCurrent(history);
printf("Bookmarked current URL.\n");
break;
case 5:
printf("Current URL after going to bookmark: %s\n",
goToBookmark(history));
break;
case 6:
displayHistory(history);
break;
case 7:
printf("Exiting the program.\n");
break;
default:
printf("Invalid choice. Please try again.\n");
}
} while (choice != 7);
// Free allocated memory
freeBrowserHistory(history);
return 0;
}
