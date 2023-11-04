#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

// BST节点定义
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {} // 添加节点高度
    int height;
};

// BST类定义
class BinarySearchTree {
private:
    TreeNode* root;

    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(TreeNode* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    
    TreeNode* insert(TreeNode* root, int key) {
        TreeNode* newNode = new TreeNode(key);
        if (root == nullptr) {
            return newNode;
        }

        if (key < root->data) {
            root->left = insert(root->left, key);
        }
        else if (key > root->data) {
            root->right = insert(root->right, key);
        }
        else {
            delete newNode;
        }

        // 添加平衡逻辑（自平衡BST的逻辑）
        int balance = getBalanceFactor(root);

        if (balance > 1) {
            if (key < root->left->data) {
                return rotateRight(root);
            }
            else {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }

        if (balance < -1) {
            if (key > root->right->data) {
                return rotateLeft(root);
            }
            else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        // 更新节点高度
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        return root;
    }


    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* remove(TreeNode* node, int key) {
        if (node == nullptr) return node;
        if (key < node->data) {
            node->left = remove(node->left, key);
        }
        else if (key > node->data) {
            node->right = remove(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    TreeNode* search(TreeNode* node, int key,int CheckCount) {
        if (node == nullptr)
        {
            cout << "未找到值,比较次数:"<<CheckCount << endl;
            return node;
        }
        CheckCount++;
        if (node->data == key) {
            cout << "已经找到：" << key <<",查找长度:" << CheckCount << endl;
            return node;
        }

        if (key < node->data) {
            return search(node->left, key,CheckCount);
        }
        return search(node->right, key,CheckCount);
    }

    void inOrderTraversal(TreeNode* node, std::vector<int>& result) {
        if (node == nullptr) return;
        inOrderTraversal(node->left, result);
        result.push_back(node->data);
        inOrderTraversal(node->right, result);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    bool search(int key) {
        return search(root, key,0) != nullptr;
    }

    std::vector<int> inOrderTraversal() {
        std::vector<int> result;
        inOrderTraversal(root, result);
        return result;
    }

};

// 折半查找函数（非递归）
int binarySearch(const std::vector<int>& arr, int key,int CheckCount) {
    int low = 0;
    int high = arr.size() - 1;
    bool find = false;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        CheckCount++;
        if (arr[mid] == key) {
            cout << "已经找到：" << key <<",查找长度："<<CheckCount << endl;
            find = true;
            return mid;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    if(!find)
    cout << "未找到值,查找长度："<<CheckCount << endl;
}

//折半查找函数（递归）
int binarySearchRecursive(const std::vector<int>& arr, int key,int low,int high,int CheckCount) {
 //   auto ptr = arr.data();
    
    if (low > high) {
        cout << "未找到值,查找长度为："<<CheckCount << endl;
        return -1; // 查找失败，元素不在数组中
    }
    int mid = low + (high - low) / 2;
    CheckCount++;
    if (arr[mid] == key) {
        cout << "已经找到：" << key <<",查找长度为："<<CheckCount << endl;
        return mid; // 找到了元素，返回索引
    }
   
    else if (arr[mid] > key) {
        high = mid - 1;
        return binarySearchRecursive(arr, key,low,high,CheckCount); // 在左半部分继续查找
    }
    else {
        low = mid + 1;
        return binarySearchRecursive(arr, key,low,high,CheckCount); // 在右半部分继续查找
    }
}

int main() {
    cout << "BST插入(建立)，删除，查找，排序的实现：" << endl;
    std::vector<int> data0;
    int arr[10] = { 5,3,9,12,23,17,26,30,21,15 };
    for (int i = 0; i <10; i++) {
        data0.push_back(arr[i]);
    }

    BinarySearchTree bst0; // 创建BST结构1
    for (int num : data0) {
        bst0.insert(num);
    }

    std::cout << "BST的插入(建立): ";
    for (int value : data0) {
        std::cout << value << " ";
    }

    std::cout << std::endl;
    bst0.remove(17);

    
    std::vector<int> sortedData0 = bst0.inOrderTraversal();
    std::cout << "BST的删除并排序(删除17): ";
    for (int value : sortedData0) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    cout << "在BST中查找17和30" << endl;
    bst0.search(17);
    bst0.search(30);
    cout << "在数组中查找17和30(非递归)" << endl;
    binarySearch(sortedData0, 17,0);
    binarySearch(sortedData0, 30,0);
    cout << "在数组中查找17和30(递归)" << endl;
    binarySearchRecursive(sortedData0, 17, 0, sortedData0.size() - 1,0);
    binarySearchRecursive(sortedData0, 30, 0, sortedData0.size() - 1,0);
    
    cout << endl;


    std::vector<int> data1; // 第一组测试数据
    for (int i = 0; i <= 8096; i+=2) {
        data1.push_back(i);
    }

    //66666667777

    std::vector<int> data2 = data1; // 第二组测试数据（随机序列）
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(data2.begin(), data2.end());

    BinarySearchTree bst1; // 创建BST结构1
    for (int num : data1) {
        bst1.insert(num);
    }

    BinarySearchTree bst2; // 创建BST结构2
    for (int num : data2) {
        bst2.insert(num);
    }

    // 比较BST查找和折半查找的性能
    std::cout << "BST查找性能比较：" << std::endl;
    for (int i = 0; i < 5; ++i) {
        int key = std::rand() % 8096; // 生成一个随机的查找键

        // BST查找
        clock_t start_time = clock();
        bst1.search(key);
        clock_t end_time = clock();
        double bst_search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        // 折半查找
        start_time = clock();
        binarySearch(data1, key, 0);
        end_time = clock();
        double binary_search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        std::cout << "查找键：" << key << " BST查找时间：" << bst_search_time << "s 折半查找时间：" << binary_search_time << "s" << std::endl;
    }
    
    return 0;
}
