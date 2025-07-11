
// FUNC: _jdiv_round_up
int __cdecl jdiv_round_up(int a, int b)
{
  return (a + b - 1) / b;
}

// FUNC: _jround_up
int __cdecl jround_up(int a, int b)
{
  return a + b - 1 - (a + b - 1) % b;
}

// FUNC: _jcopy_sample_rows
void __cdecl jcopy_sample_rows(
        unsigned __int8 **input_array,
        int source_row,
        unsigned __int8 **output_array,
        int dest_row,
        int num_rows,
        unsigned int num_cols)
{
  int v6; // ebx
  const void **v7; // eax
  void **v8; // edx

  v6 = num_rows;
  v7 = (const void **)&input_array[source_row];
  v8 = (void **)&output_array[dest_row];
  if ( num_rows > 0 )
  {
    do
    {
      qmemcpy(*v8++, *v7++, num_cols);
      --v6;
    }
    while ( v6 );
  }
}

// FUNC: _jzero_far
void __cdecl jzero_far(void *target, unsigned int bytestozero)
{
  memset(target, 0, bytestozero);
}
