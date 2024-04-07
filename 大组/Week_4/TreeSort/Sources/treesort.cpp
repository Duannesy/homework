#include<bits/stdc++.h>
using namespace std;
// ����������ڵ�ṹ��
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// �����½ڵ�
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;//�����нڵ��ʼ�� 
    return newNode;
}
int searchInBST(TreeNode *root, int data) {
    if (root == NULL) {
        return 0;
    }

    if (root->val == data) {
        return 1;
    } else if (data < root->val) {
        return searchInBST(root->left, data);
    } else {
        return searchInBST(root->right, data);
    }
}
int findPositionInBST(TreeNode *root, int data, int position) {
    if (root == NULL) {
        return -1; // ���ݲ��ڶ�����������
    }

    if (root->val == data) {
        return position; // �����ҵ����ݵ�λ��
    } else if (data < root->val) {
        return findPositionInBST(root->left, data, position * 2); // ���������м���������λ�üӱ�
    } else {
        return findPositionInBST(root->right, data, position * 2 + 1); // ���������м���������λ�üӱ���һ
    }
}
// ����ڵ�
TreeNode *insert(TreeNode *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->val) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    return root;
}

// ������С�ڵ�

TreeNode *findMin(TreeNode *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
// ɾ���ڵ�
TreeNode *remove(TreeNode *root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->val) {
        root->left = remove(root->left, data);
    } else if (data > root->val) {
        root->right = remove(root->right, data);
    } else {
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        TreeNode *temp = findMin(root->right);
        root->val = temp->val;
        root->right = remove(root->right, temp->val);
    }

    return root;
}

// ǰ�����
void preOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

// �������
void inOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

// �������
void postOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}
//�ǵݹ�ǰ����� 
void preordertra(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    stack<TreeNode*> s;//����ջ����������ȱ��� 
    s.push(root);

    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        printf("%d ", node->val);

        if (node->right) {
            s.push(node->right);
        }
        if (node->left) {
            s.push(node->left);
        }
    }
}
//�ǵݹ�������� 
void inordertra(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* current = root;

    while (current != NULL || !s.empty()) {
        while (current != NULL) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();
        printf("%d ", current->val);

        current = current->right;
    }
}
//�ǵݹ�������� 
void postordertra(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    stack<TreeNode*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        TreeNode* node = s1.top();
        s1.pop();
        s2.push(node);

        if (node->left) {
            s1.push(node->left);
        }
        if (node->right) {
            s1.push(node->right);
        }
    }

    while (!s2.empty()) {
        TreeNode* node = s2.top();
        s2.pop();
        printf("%d ", node->val);
    }
}
// �������
void levelOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        printf("%d ", current->val);
        if (current->left != NULL) {
            q.push(current->left);
        }
        if (current->right != NULL) {
            q.push(current->right);
        }
    }
}

int main()
{
	TreeNode* root = NULL;//��ʼ������������
	int in=0;
	int out=0;
	int find=0;
	int a;
	printf("----����������-----\n");
	printf("1.����ڵ�\n");
	printf("2.ɾ���ڵ�\n");
	printf("3.���ҽڵ�λ��\n");
	printf("4.���ֵݹ������������չʾ\n");
	printf("5.���ַǵݹ����չʾ\n");
	printf("0.�˳�\n");
	printf("������������룺");
	do{
		scanf("%d",&a);
		if(a==0)  break;
		else{
			switch(a){
				case 1:
					printf("������Ҫ���������");
					scanf("%d",&in); 
					root=insert(root,in); 
					printf("������������룺");
					break;
				case 2:
					printf("������Ҫɾ��������");
					int out;
					scanf("%d",&out); 
					if(searchInBST(root,out)==0){
						printf("�Ҳ���������\n"); 
					}
					else{
						root=remove(root,out);
					} 
					printf("������������룺");
					break;
				case 3:
					int find,pos;
					printf("������Ҫ����λ�õ�����"); 
					scanf("%d",&find);
					if(searchInBST(root,find)==0){
						printf("�Ҳ���������\n"); 
					}
					else{
						pos=findPositionInBST(root,find,1);
						printf("λ��Ϊ%d\n",pos);
					}
					printf("������������룺");
					break;
				case 4:
					printf("ǰ�������");
					preOrder(root);
					printf("\n");
					printf("���������");
					inOrder(root);
					printf("\n");
					printf("���������");
					postOrder(root);
					printf("\n");
					printf("���������");
					levelOrder(root);
					printf("\n");
					printf("������������룺");
					break;
				case 5:
					printf("�ǵݹ�ǰ�������");
					preordertra(root);
					printf("\n");
					printf("�ǵݹ����������");
					inordertra(root);
					printf("\n");
					printf("�ǵݹ���������");
					postordertra(root);
					printf("\n");
					printf("������������룺");
					break;
					printf("������������룺");
					break;
				
			}
		}
	}while(a!=0);
}
