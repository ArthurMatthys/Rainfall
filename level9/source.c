
/* N::N(int) */

void __thiscall N(N *this,int param_1)

{
  *(undefined4 *)this = 0x8048848;
  *(int *)(this + 0x68) = param_1;
  return;
}

/* N::setAnnotation(char*) */

void __thiscall setAnnotation(N *this,char *param_1)

{
  size_t __n;

  __n = strlen(param_1);
  memcpy(this + 4,param_1,__n);
  return;
}

void main(int param_1,int param_2)

{
  N *this;
  code **this_00;

  if (param_1 < 2) {
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  this = (N *)operator.new(0x6c);
  N(this,5);
  this_00 = (code **)operator.new(0x6c);
  N((N *)this_00,6);
  setAnnotation(this,*(char **)(param_2 + 4));
  (**(code **)*this_00)(this_00,this);
  return;
}
