#include "AVLTree.h"

int AVLTree::height(Node* n) {//υπολογισμός του ύψους του δέντρου
  return n ? n->height : 0;// αν το δέντρο δεν είναι άδειο τότε επιστρέφουμε το ύψοσ αλλιώσ 0
}

int AVLTree::getBalance(Node* n) {//υπολογισμός της διαφοράς των δύο υποδέντρων 
  return n ? height(n->left) - height(n->right) : 0;
}

int AVLTree::max(int a, int b) {
  return (a > b) ? a : b;
}

Node* AVLTree:: rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;//υπολογισμός του ύψους του δέντρου 
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* AVLTree::leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

Node* AVLTree:: insert(Node* node, int key) {
  if (!node) {//αν το δέντρο είναι άδειο τότε εισάγουμε το στοιχείο και αυξάνουμε το μέγεθος του δέντρου και επιστρέφουμε το στοιχείο
      size++;
      return new Node(key);
  }
  if (key < node->key)
      node->left = insert(node->left, key);//αν τα στοιχεία είναι μικρότερα από το στοιχείο που εισάγουμε τότε εισάγουμε το στοιχείο αριστερά αλλιώς δεξιά
  else if (key > node->key)
      node->right = insert(node->right, key);
  else
      return node;

  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key)//αν η διαφορά των δύο υποδέντρων είναι μεγαλύτερη από 1 και το στοιχείο που  εισάγουμε είναι μικρότερο από το στοιχείο που εισάγουμε τότε κανουμε αριστερή περιστροφή αλλιως δεξια
      return rightRotate(node);
  if (balance < -1 && key > node->right->key)
      return leftRotate(node);
  if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
  }
  if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
  }

  return node;
}

Node* AVLTree:: minValueNode(Node* node) {
  Node* current = node;
  while (current->left)
      current = current->left;
  return current;
}



Node* AVLTree:: deleteNode(Node* root, int key) {
  if (!root) return root;

  if (key < root->key)
      root->left = deleteNode(root->left, key);
  else if (key > root->key)
      root->right = deleteNode(root->right, key);
  else {
      if (!root->left || !root->right) {
          Node* temp = root->left ? root->left : root->right;
          if (!temp) {
              temp = root;
              root = nullptr;
          } else {
              *root = *temp;
          }
          delete temp;
          size--;
      } else {
          Node* temp = minValueNode(root->right);
          root->key = temp->key;
          root->right = deleteNode(root->right, temp->key);
      }
  }

  if (!root) return root;

  root->height = 1 + max(height(root->left), height(root->right));
  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0)
      return rightRotate(root);
  if (balance > 1 && getBalance(root->left) < 0) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0)
      return leftRotate(root);
  if (balance < -1 && getBalance(root->right) > 0) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
  }

  return root;
}

bool AVLTree::search(Node* node, int key) {
  if (!node) return false;
  if (node->key == key) return true;
  return key < node->key ? search(node->left, key) : search(node->right, key);//αν το στοιχείο που αναζητούμε είναι μικρότερο από το στοιχείο που αναζητούμε τότε αναζητούμε αριστερά αλλίωσ δεξια 
}

int AVLTree::findMin(Node* node) {
  Node* current = node;
  while (current && current->left)
      current = current->left;
  return current ? current->key : INT_MIN;//αν το δέντρο δεν είναι άδειο τότε επιστρέφουμε το ελάχιστο στοιχείο αλλιωσ επιστρέφουμε το ελάχιστο ακέραιο
}

void AVLTree::insert(int key) {
  root = insert(root, key);
}

void AVLTree::deleteKey(int key) {
  root = deleteNode(root, key);
}

bool AVLTree:: search(int key) {
  return search(root, key);
}


int AVLTree::findMin() {
  return findMin(root);
}
int AVLTree:: getSize() {
  return size;
}

void AVLTree:: buildFromFile(string& filename) {
  ifstream file(filename);
  int value;
  while (file >> value) {
      insert(value);
  }
  file.close();
}