/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef UTIL_LINKEDLIST_H_
#error "Do not include this .tcc file directly, use the .h file"
#else

template <typename T>
LinkedList<T>::LinkedList() : head_(NULL), count_(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
  Cell* next;
  while (head_ != NULL) {
    next = head_->next;
    delete head_;
    head_ = next;
  }
}

template <typename T>
size_t LinkedList<T>::size() const {
  return count_;
}

template <typename T>
void LinkedList<T>::push(T* item) {
  Cell* prev = NULL;
  Cell* curr = head_;
  while (curr != NULL) {
    prev = curr;
    curr = curr->next;
  }

  Cell* newCell = new Cell();
  newCell->next = NULL;
  newCell->item = item;

  if (prev == NULL) {
    head_ = newCell;
  } else {
    prev->next = newCell;
  }

  count_++;
}

#endif  // UTIL_LINKEDLIST_H_
