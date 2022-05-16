/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n");
		printf("[----- [���°�] [2019038059] -----]\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//������ ����h�� ��� ��ŭ �޸� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)//������ȸ
{
	if(ptr) {
		recursiveInorder(ptr->left);//����Լ��� ���ؼ� ptr�� �����ڽ����� ����Ŵ
		printf(" [%d] ", ptr->key);//ptr�� ���� ���
		recursiveInorder(ptr->right);//����Լ��� ���ؼ� ptr�� ������ �ڽ����� ����Ŵ
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)//�ݺ��� ���� ��ȸ
{
	for(;;)//���ѷ�Ʈ
	{
		for(; node; node = node->left)//node��NULL�� �ƴϸ� ���� ��带 �����ڽ����� �ٱ���
			push(node);//���ÿ� ����
		node = pop();//���ÿ��� ����

		if(!node) break;//���� �����϶� ����
		printf(" [%d] ", node->key);

		node = node->right;//�������� �������ڽ��� ����Ŵ 
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)//�������� ��ȸ 
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);//ptr�� ť�ȿ� �Է�

	for(;;)//���� ��Ʈ
	{
		ptr = deQueue();//ť���� �������� ��尡 ptr
		if(ptr) {//ptr�� NULL �̾ƴϸ�
			printf(" [%d] ", ptr->key);//ptr�� key�� ���

			if(ptr->left)//ptr�� ���� �ڽ��� ������
				enQueue(ptr->left);//ť�ȿ� ptr�����ڽ� �Է�
			if(ptr->right)//ptr�� ������ �ڽ��� ������
				enQueue(ptr->right);//ť�ȿ� ptr������ �ڽ� �Է�
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//���ο� ��带 �޸𸮸� ��常ŭ �Ҵ�
	newNode->key = key;//���ο����� key���� �Է¹��� key���� �־���
	newNode->left = NULL;//���ο����� �����ڽ��� NULL
	newNode->right = NULL;//���ο����� ������ �ڽ��� NULL

	if (head->left == NULL) {//�������ڽ��� NULL�̸� �� ó�� ��带 �Է¹޴� �ٸ�
		head->left = newNode;//������� �����ڽ��� ���ο��带 ����Ű����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr�� head����� ���� �ڽ�

	Node* parentNode = NULL;//parentNOde�� NULL
	while(ptr != NULL) {//ptr�� NULL�ϋ����� �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;//�Է¹��� Ű���� �̹� ������ �Լ�����

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//�Է¹��� Ű���� ptr�� Ű������ ũ��
			ptr = ptr->right;//ptr�� ptr�� right�� �ٲ���
		else//�Է¹��� Ű���� ptr�� Ű������ ������
			ptr = ptr->left;//ptr�� ptr��left�� �ٱ���
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//parent����� Ű���� �Է¹��� Ű������ ũ��
		parentNode->left = newNode;//���ο��带 parent����� �����ڽ����� ����Ű����
	else
		parentNode->right = newNode;//���ο��带 parent����� �������ڽ����� ����Ű����
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {//initializeBST�Լ��� ������� �������
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//�Է¹��� ��尡 ���°��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;//root�� ù��° �Է¹��� ���



	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {//ptr��NULL�̰ų� ptr��key���� �Է����� key���̶� ���� �������ݺ�
		if(ptr->key != key) {//ptr�� key���� �Է¹��� key���̶� �ٸ����

			parent = ptr;	/* save the parent */

			if(ptr->key > key)//ptr�� key���� �Է¹��� key������ ū���
				ptr = ptr->left;//ptr�� ptr��left�� �ٱ���
			else
				ptr = ptr->right;//ptr�� ptr�� right�� �ٱ���
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)//ptr�� �����ڽ��̶� �������ڽ��� ���°�� �� ptr�� leaf��� �ΰ��
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)//parent�����ڽ��� ptr�ΰ��
				parent->left = NULL;//parnt�����ڽ��� ����
			else
				parent->right = NULL;//parnt�� ������ �ڽ��� ����
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;//head�ǿ��� �ڽ��� ���� �� root�� ����

		}

		free(ptr);//ptr�� �޸��Ҵ� ����
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))//ptr�� �ڽ��� �ϳ� �ִ°��
	{
		Node* child;
		if (ptr->left != NULL)//ptr�� ���� �ڽ��� �ִ°��
			child = ptr->left;//child ��  ptr�� �����ڽ����� ��
		else
			child = ptr->right;//child�� ptr�� ���� �� �ڽ�������

		if(parent != NULL)//parent��尡 NULL�� �ƴҰ��
		{
			if(parent->left == ptr)//parent �����ڽ��� ptr�ϰ��
				parent->left = child;//parent ���� �ڽ��� child�� ����Ű����
			else//parent ������ �ڽ��� ptr�� ���
				parent->right = child;//parent������ �ڽ��� child�� ����Ű����
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);//ptr�޸��Ҵ� ����
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;//candidate �� ptr�� ������ �ڽ�������

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)//candiate�� �����ڽ��� NULL�϶� ���� �ݺ�
	{
		parent = candidate;//parnt�� candidate�� �ٱ���
		candidate = candidate->left;//candidate�� candidate�����ڽ����� �ٱ���
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)//parnet�� �������ڽ���candiate�ϰ��
		parent->right = candidate->right;//parent�������ڽ��� candidate�� �������ڽ�
	else
		parent->left = candidate->right;//parent�����ڽ��� candidate�� �������ڽ�

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;//ptr�� Ű���� candidate�� key������ �ٱ���

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);//ptr�� ���� ��� �޸� �Ҵ� ����
		freeNode(ptr->right);//ptr�� ������ ��� �޸� �Ҵ� ����
		free(ptr);//ptr �޸� �Ҵ� ����
	}
}

int freeBST(Node* head)
{

	if(head->left == head)//head�� ���ʳ�尡 head���
	{
		free(head);//head�޷θ� �Ҵ� ����
		return 1;
	}

	Node* p = head->left;//������ p������ head�� ���� �ڽ����� �� ��p�� root���

	freeNode(p);//root��� �޸� �Ҵ�����

	free(head);//head �޸� �Ҵ� ����
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];//stack�� top�� �������ְ� top���� -1����
}

void push(Node* aNode)
{
	stack[++top] = aNode;//stack�� top���� +1�� ���� ���� aNode �Է�
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];//ť�迭�� front �ε��� ��ȣ ����

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;//ť�� rear�� aNOde�Է�
}




