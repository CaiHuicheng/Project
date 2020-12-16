class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
       ostringstream ss;
       serialize(root, ss);
       return ss.str();
    }

    TreeNode* deserialize(string data) {
       istringstream ss(data);
       return deserialize(ss);
    }

private:
    void serialize(TreeNode* root, ostringstream& ss) {
        if (!root) {
            ss << "# ";
            return;
        }

        ss << to_string(root->val) << " ";
        serialize(root->left, ss);
        serialize(root->right, ss);
    }

    TreeNode* deserialize(istringstream& ss) {
        TreeNode* root;
        string str;
        ss >> str;
        if (str == "#") {
            root = nullptr;
        } else {
            root = new TreeNode(stoi(str));
            auto left = deserialize(ss);
            auto right = deserialize(ss);
            root->left = left;
            root->right = right;
        }

        return root;
    }
};