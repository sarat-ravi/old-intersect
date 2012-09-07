import numpy as np
import mlpy
import matplotlib.pyplot as plt
import matplotlib

iris = np.loadtxt('../testfiles/iris.csv', delimiter=',')
x, y = iris[:, :4], iris[:, 4].astype(np.int)

pca = mlpy.PCA() # new PCA instance
pca.learn(x) # learn from data
z = pca.transform(x, k=2)

#plt.set_cmap(plt.cm.Paired)
fig1 = plt.figure(1)
title = plt.title("PCA on iris dataset")
plot = plt.scatter(z[:, 0], z[:, 1], c=y)
labx = plt.xlabel("First component")
laby = plt.ylabel("Second component")
#plt.show()

svm = mlpy.LibSvm(kernel_type='linear')
svm = mlpy.LibSvm(kernel_type='poly')
svm = mlpy.LibSvm(kernel_type='rbf')
svm = mlpy.LibSvm(kernel_type='rbf', svm_type='c_svc', gamma=10)
svm.learn(z, y) # learn from principal components

#graphing vars
xmin, xmax = z[:,0].min()-0.1, z[:,0].max()+0.1
ymin, ymax = z[:,1].min()-0.1, z[:,1].max()+0.1
xx, yy = np.meshgrid(np.arange(xmin, xmax, 0.01), np.arange(ymin, ymax, 0.01))
zgrid = np.c_[xx.ravel(), yy.ravel()]

yp = svm.pred(zgrid)
print zgrid
#plt.set_cmap(plt.cm.Paired)
fig2 = plt.figure(2)
title = plt.title("SVM on principal components")
plot1 = plt.pcolormesh(xx, yy, yp.reshape(xx.shape))
plot2 = plt.scatter(z[:, 0], z[:, 1], c=y)
labx = plt.xlabel("First component")
laby = plt.ylabel("Second component")
limx = plt.xlim(xmin, xmax)
limy = plt.ylim(ymin, ymax)
plt.show()
