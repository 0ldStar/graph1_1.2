import matplotlib.pyplot as plt
import numpy as np

cpu = np.transpose(np.loadtxt('cmake-build-debug/write.txt'))
xc = np.arange(1, len(cpu[0]) + 1)
plt.plot(xc, cpu[0], label='cpu')
plt.ylabel('time, msec')
plt.xlabel('matrix size')
plt.grid()
plt.legend()
plt.show()