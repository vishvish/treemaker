#ifndef _TMTREE_FWD_H_
#define _TMTREE_FWD_H_

// Forward declarations
class tmTree;

// Helper class for tmTree cleanup
class tmTreeCleaner {
public:
  tmTreeCleaner(tmTree* aTree);
  ~tmTreeCleaner();
  
  tmTree* GetTree() const {
    return mTree;
  }
  
private:
  tmTree* mTree;
  bool mNeedsCleanup;
};

#endif // _TMTREE_FWD_H_
