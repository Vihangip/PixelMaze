
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

/* node constructor given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, HSLAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),LT(NULL),RB(NULL)
	{}

/* destructor given */
twoDtree::~twoDtree(){
	clear();
}

/* copy constructor given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


/* operator= given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

/* twoDtree constructor */
twoDtree::twoDtree(PNG & imIn){
    stats stat_obj(imIn);
    pair<int,int> ul (0,0);
    pair<int,int> lr (imIn.width() - 1, imIn.height() - 1);

    width = imIn.width();
    height = imIn.height();
    bool vert = true;
    root = buildTree(stat_obj, ul, lr,vert);

}

/* buildTree helper for twoDtree constructor */
twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {
    HSLAPixel averagePixel = s.getAvg(ul, lr);
    Node *node = new Node(ul, lr, averagePixel);

    //Base Case
    if(ul.first == lr.first && ul.second == lr.second) {
        return node;
    }

    pair<int, int> new_ul = ul;
    pair<int, int> new_lr = lr;
    // calculateNewCoords(s, new_ul, new_lr, vert); // computes new_ul and new_lr that results in smallest weighted sum of entropies

//    if(new_ul == ul && new_lr == lr) {
//        return node;
//    }

    //Horizontal Row Case

    if(ul.second == lr.second && lr.first - ul.first > 0) {
        calculateNewCoords(s, new_ul, new_lr, true);
        node->LT = buildTree(s, ul, new_lr, false);
        node->RB = buildTree(s, new_ul, lr, false);
        return node;


        //Vertical Column Case

    } else if(ul.first == lr.first && lr.second - ul.second > 0) {
        calculateNewCoords(s, new_ul, new_lr, false);
        node->LT = buildTree(s, ul, new_lr, true);
        node->RB = buildTree(s, new_ul, lr, true);
        return node;

        //Vertical Split

    } else if (vert) {
        // cout << ul.first;
        // cout << lr.second;
        calculateNewCoords(s, new_ul, new_lr, vert);

        node->LT = buildTree(s, ul, new_lr, false);
        node->RB = buildTree(s, new_ul, lr, false);

        return node;

        //Horizontal Split
    } else {
        // cout << ul.first;
        // cout << lr.second;
        calculateNewCoords(s, new_ul, new_lr, vert);

        node->LT = buildTree(s, ul, new_lr, true);
        node->RB = buildTree(s, new_ul, lr, true);

        return node;

    }

}

void twoDtree::calculateNewCoords(stats &stats, pair<int, int>& ul, pair<int, int>& lr, bool vert) {
    long smallestEntropy;
    pair<int,int> smallestEntropyLr;
    pair<int,int> smallestEntropyUl;


    if(vert){
        smallestEntropyUl = {ul.first + 1, ul.second};
        smallestEntropyLr = {ul.first, lr.second};
        smallestEntropy = weightedEntropy(stats,ul,smallestEntropyLr) + weightedEntropy(stats,smallestEntropyUl,lr);

        for(int x = ul.first + 1; x <= lr.first - 1; x++) {
//            cout << " x";
            //cout << x;
            pair<int,int> newUl = {x + 1, ul.second};
            pair<int,int> newLr = {x, lr.second};



            long currEntropy = weightedEntropy(stats,ul,newLr) + weightedEntropy(stats,newUl,lr);
            if(currEntropy <= smallestEntropy){
                //cout << "beep";
                smallestEntropy = currEntropy;
                smallestEntropyUl = newUl;
                smallestEntropyLr = newLr;
            }
        }

    } else {
        smallestEntropyUl = {ul.first, ul.second + 1};
        smallestEntropyLr = {lr.first, ul.second};
        smallestEntropy = weightedEntropy(stats,ul,smallestEntropyLr) + weightedEntropy(stats, smallestEntropyUl, lr);

        for(int y = ul.second + 1; y <= lr.second - 1; y++){
//            cout << " y";
//            cout << y ;
            pair<int,int> newUl = {ul.first, y + 1};
            pair<int,int> newLr = {lr.first, y};


            long currEntropy = weightedEntropy(stats,ul,newLr) + weightedEntropy(stats,newUl,lr);
            if(currEntropy <= smallestEntropy) {
                //cout << "boop";
                smallestEntropy = currEntropy;
                smallestEntropyUl = newUl;
                smallestEntropyLr = newLr;
            }
        }
    }

    ul = smallestEntropyUl;
    lr = smallestEntropyLr;

}

double twoDtree::weightedEntropy(stats &s, pair<int, int> ul, pair<int, int> lr) {
    double totalEntropy = s.entropy(ul,lr);
    double totalArea = s.rectArea(ul,lr);

    return totalEntropy/totalArea;
}

/* render your twoDtree into a png */
PNG twoDtree::render(){
    PNG img (width, height);
    Node* curr = root;
    renderHelper(img, curr);
    return img;
}

void twoDtree::renderHelper(PNG &img, Node *curr) {
    if (curr->LT == NULL && curr->RB == NULL)
    {
        pair<int,int> ul = curr->upLeft;
        pair<int,int> lr = curr->lowRight;

        for (int i = ul.first; i <= lr.first; ++i)
        {
            for (int j = ul.second; j <= lr.second; ++j)
            {
                HSLAPixel* pixel = img.getPixel(i,j);
                *pixel = curr->avg;
            }
        }
    }

    else
    {
        if (curr->LT != NULL)
            renderHelper(img, curr->LT);

        if (curr->RB != NULL)
            renderHelper(img, curr->RB);
    }
}


/* prune function modifies tree by cutting off
 * subtrees whose leaves are all within tol of 
 * the average pixel value contained in the root
 * of the subtree
 */
void twoDtree::prune(double tol){
    pruneHelper(root,tol);

}

void twoDtree::pruneHelper(twoDtree::Node *subtree, double tol) {

    if (subtree->LT == NULL && subtree->RB == NULL)	{ //leaf node
        return;
    }


    double prunableLeafNodes = 0;
    double totalLeafNodes = 0;
    shouldBePruned(subtree, subtree->avg, tol, prunableLeafNodes, totalLeafNodes);



    if (prunableLeafNodes == totalLeafNodes)
    {
        clearAll(subtree->LT);
        clearAll(subtree->RB);
        subtree->LT = NULL;
        subtree->RB = NULL;
    }

    else
    {
        if (subtree->LT != NULL) {
            pruneHelper(subtree->LT, tol);
        }


        if (subtree->RB != NULL) {
            pruneHelper(subtree->RB, tol);
        }

    }
}

void twoDtree::shouldBePruned(Node *subtree, HSLAPixel pixel, double tol, double& prunable, double& total) {
    if (subtree->LT == NULL && subtree->RB== NULL)
    {
        total++;
        HSLAPixel subtreePixel = subtree->avg;

        //long distBetweenCols = subtreePixel.dist(pixel);

        double distBetweenCols = pixel.dist(subtreePixel);

        if (distBetweenCols <= tol)
            prunable++;
    }

    else
    {

        if (subtree->RB != NULL) {
            shouldBePruned (subtree->RB, pixel, tol, prunable, total);

        }

        if (subtree->LT != NULL) {
            shouldBePruned (subtree->LT, pixel, tol, prunable, total);

        }




    }
}

/* helper function for destructor and op= */
/* frees dynamic memory associated w the twoDtree */
void twoDtree::clear() {
    clearAll(root);
    width = 0;
    height = 0;
}

void twoDtree::clearAll(Node *subRoot) {
    if (subRoot == NULL)
        return;

    else {
        clearAll(subRoot->LT);
        clearAll(subRoot->RB);
        delete subRoot;
    }
}


/* helper function for copy constructor and op= */
void twoDtree::copy(const twoDtree & orig){
    root = copyAll(orig.root);
    width = orig.width;
    height = orig.height;

}

twoDtree::Node *twoDtree::copyAll(twoDtree::Node *tree) {
    Node* curr = new Node(tree->upLeft, tree->lowRight, tree->avg);

    if (tree->LT != NULL)
        curr->LT = copyAll(tree->LT);

    if (tree->RB != NULL)
        curr->RB = copyAll(tree->RB);

    return curr;
}












