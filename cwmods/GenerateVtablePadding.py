with open('VtablePadding.h', 'w') as f:
    for i in range(1024):
        f.write(f'Priority DummyCallbackPriority_{i} = NormalPriority;\n')
        f.write(f'virtual int DummyCallback_{i}(void* a1, void* a2, void* a3, void* a4)' + '{return 0;} \n')
