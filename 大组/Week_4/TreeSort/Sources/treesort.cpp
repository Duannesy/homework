#include<bits/stdc++.h>
using namespace std;
// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 创建新节点
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;//将所有节点初始化 
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
        return -1; // 数据不在二叉搜索树中
    }

    if (root->val == data) {
        return position; // 返回找到数据的位置
    } else if (data < root->val) {
        return findPositionInBST(root->left, data, position * 2); // 在左子树中继续搜索，位置加倍
    } else {
        return findPositionInBST(root->right, data, position * 2 + 1); // 在右子树中继续搜索，位置加倍加一
    }
}
// 插入节点
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

// 查找最小节点

TreeNode *findMin(TreeNode *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
// 删除节点
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

// 前序遍历
void preOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

// 中序遍历
void inOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

// 后序遍历
void postOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}
//非递归前序遍历 
void preordertra(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    stack<TreeNode*> s;//利用栈进行深度优先遍历 
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
//非递归中序遍历 
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
//非递归后续遍历 
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
// 层序遍历
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
	TreeNode* root = NULL;//初始化二叉搜索树
	int in=0;
	int out=0;
	int find=0;
	int a;
	printf("----二叉排序树-----\n");
	printf("1.插入节点\n");
	printf("2.删除节点\n");
	printf("3.查找节点位置\n");
	printf("4.三种递归遍历与层序遍历展示\n");
	printf("5.三种非递归遍历展示\n");
	printf("0.退出\n");
	printf("请输入操作代码：");
	do{
		scanf("%d",&a);
		if(a==0)  break;
		else{
			switch(a){
				case 1:
					printf("请输入要插入的数据");
					scanf("%d",&in); 
					root=insert(root,in); 
					printf("请输入操作代码：");
					break;
				case 2:
					printf("请输入要删除的数据");
					int out;
					scanf("%d",&out); 
					if(searchInBST(root,out)==0){
						printf("找不到该数据\n"); 
					}
					else{
						root=remove(root,out);
					} 
					printf("请输入操作代码：");
					break;
				case 3:
					int find,pos;
					printf("请输入要查找位置的数据"); 
					scanf("%d",&find);
					if(searchInBST(root,find)==0){
						printf("找不到该数据\n"); 
					}
					else{
						pos=findPositionInBST(root,find,1);
						printf("位置为%d\n",pos);
					}
					printf("请输入操作代码：");
					break;
				case 4:
					printf("前序遍历：");
					preOrder(root);
					printf("\n");
					printf("中序遍历：");
					inOrder(root);
					printf("\n");
					printf("后序遍历：");
					postOrder(root);
					printf("\n");
					printf("层序遍历：");
					levelOrder(root);
					printf("\n");
					printf("请输入操作代码：");
					break;
				case 5:
					printf("非递归前序遍历：");
					preordertra(root);
					printf("\n");
					printf("非递归中序遍历：");
					inordertra(root);
					printf("\n");
					printf("非递归后序遍历：");
					postordertra(root);
					printf("\n");
					printf("请输入操作代码：");
					break;
					printf("请输入操作代码：");
					break;
				
			}
		}
	}while(a!=0);
}
