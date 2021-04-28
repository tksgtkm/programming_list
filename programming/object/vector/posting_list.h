#ifndef __POSTINGLIST_H
#define __POSTINGLIST_H

#include <vector>

class PostingList {
public:
  int document_id;
  vector<int> positions;
  int positions_count;
  struct PostingList *next;
}

#endif
