ListNode* mergeSort(ListNode* bfirst, int len) {
    auto bmid = bfirst->next;
    for (int l = 1;l < len;l <<= 1) {
        const int remain = min(l, len - l);
        auto blast = mergeSort(bmid, remain);
        bmid = inplaceMerge(bfirst, bmid, blast);
    }
    return bmid;
}

ListNode* sortList(ListNode* head) noexcept {
    ListNode node(0, head), *sen = &node;
    mergeSort(sen, getLength(head));
    return node.next;
}
