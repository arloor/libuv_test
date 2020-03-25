## example 看example.c


## uv_buf_t uv_buf_init(char* base, unsigned int len) 谁来free这个buf

答案： uv_buf_init只是传递buf，只需要在回调中进行free，并且如果buf是在栈中声明，则不需要free。

注意，free(void*)而不是free(const void *)所以const char *无法被直接释放，除非强转成 oid *
   
   Don't worry about the struct, but worry about what it points to.
   
   If the function you pass the uv_buf_t to is used in an asynchronous way the memory that uv_buf_t.base points to must not be freed until the callback is called.
   
   Even cancelling in progress requests like uv_write_t (by calling close on the handle) does not prevent the callbacks from getting called, so it's safe to do the cleanup there.
   
 ## uv_tcp_t在nread=0时，需要uv_close，然后在回调中free