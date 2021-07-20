an multi-consumer/producer linked-list but no any protection
so it should be unsafe

- file
    - test_list.c
        - test the function of list
    - test.c
        - test the list in multi-consumer/producer

- Result
    - unsafe, for multiple putter and single taker, sometimes taker will enter a infinite loop to take nothing; for single putter and single taker, sometimes sum will be wrong.
