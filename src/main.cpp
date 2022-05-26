#include "./extends/functions.cpp"

int main()
{
  pri = (struct queue **)calloc(41, sizeof(struct queue *));

  for (int i = 0; i < 41; i++)
  {
    pri[i] = NULL;
  }

  char const *fname = "test.data";

  getDataFromFile(fname);

  Print();

  return 0;
}
