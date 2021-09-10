#import tensorflow as tf
import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()
import numpy as np
import matplotlib.pyplot as plt
# 下面这一行代码就可以直接从官网下载数据，下载完之后，你应该可以在目录中发现一个新文件夹“MNIST_data”
from tensorflow.examples.tutorials.mnist import input_data 
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

X_train,Y_train = mnist.train.images,mnist.train.labels
X_test,Y_test = mnist.test.images,mnist.test.labels
# 不妨看看它们的形状：
print(X_train.shape)  # (55000, 784)
print(Y_train.shape)  # (55000, 10)
print(X_test.shape)   # (10000, 784)
print(Y_test.shape)   # (10000, 10)

tf.reset_default_graph() # 这个可以不用细究，是为了防止重复定义报错
 
# 给X、Y定义placeholder，要指定数据类型、形状：
X = tf.placeholder(dtype=tf.float32,shape=[None,784],name='X')
Y = tf.placeholder(dtype=tf.float32,shape=[None,10],name='Y')
 
# 定义各个参数：
W1 = tf.get_variable('W1',[784,128],initializer=tf.truncated_normal_initializer())
b1 = tf.get_variable('b1',[128],initializer=tf.zeros_initializer())
W2 = tf.get_variable('W2',[128,64],initializer=tf.truncated_normal_initializer())
b2 = tf.get_variable('b2',[64],initializer=tf.zeros_initializer())
W3 = tf.get_variable('W3',[64,10],initializer=tf.truncated_normal_initializer())
b3 = tf.get_variable('b3',[10],initializer=tf.zeros_initializer())

A1 = tf.nn.relu(tf.matmul(X,W1)+b1,name='A1')
A2 = tf.nn.relu(tf.matmul(A1,W2)+b2,name='A2')
Z3 = tf.matmul(A2,W3)+b3

cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=Z3,labels=Y))

trainer = tf.train.AdamOptimizer().minimize(cost)

with tf.Session() as sess:
    # 首先给所有的变量都初始化（不用管什么意思，反正是一句必须的话）：
    sess.run(tf.global_variables_initializer())
 
    # 定义一个costs列表，来装迭代过程中的cost，从而好画图分析模型训练进展
    costs = []
   
    # 指定迭代次数：
    for it in range(1000):
        # 这里我们可以使用mnist自带的一个函数train.next_batch，可以方便地取出一个个地小数据集，从而可以加快我们的训练：
        X_batch,Y_batch = mnist.train.next_batch(batch_size=64)
 
        # 我们最终需要的是trainer跑起来，并获得cost，所以我们run trainer和cost，同时要把X、Y给feed进去：
        _,batch_cost = sess.run([trainer,cost],feed_dict={X:X_batch,Y:Y_batch})
        costs.append(batch_cost)
# conda install -c jjh_pytorch pytorch-cpu torchvision-cpu
        # 每100个迭代就打印一次cost：
        if it%100 == 0:
            print('iteration%d ,batch_cost: '%it,batch_cost)
    # 训练完成，我们来分别看看来训练集和测试集上的准确率：
    predictions = tf.equal(tf.argmax(tf.transpose(Z3)),tf.argmax(tf.transpose(Y)))
    accuracy = tf.reduce_mean(tf.cast(predictions,'float'))
    print("Training set accuracy: ",sess.run(accuracy,feed_dict={X:X_train,Y:Y_train}))
    print("Test set accuracy:",sess.run(accuracy,feed_dict={X:X_test,Y:Y_test}))

# 这里改了一点上面的预测集准确率的代码，因为我们需要知道预测结果，所以这里我们单独把Z3的值给取出来，这样通过分析Z3，即可知道预测值是什么了。
    z3,acc = sess.run([Z3,accuracy],feed_dict={X:X_test,Y:Y_test})
    print("Test set accuracy:",acc)
   
    # 随机从测试集中抽一些图片（比如第i*10+j张图片），然后取出对应的预测（即z3[i*10+j]）：
    fig,ax = plt.subplots(4,4,figsize=(15,15))
    fig.subplots_adjust(wspace=0.1, hspace=0.7)
    for i in range(4):
        for j in range(4):
           ax[i,j].imshow(X_test[i*10+j].reshape(28,28))
            # 用argmax函数取出z3中最大的数的序号，即为预测结果：
           predicted_num  = np.argmax(z3[i*10+j])       
            # 这里不能用tf.argmax，因为所有的tf操作都是在图中，没法直接取出来
           ax[i,j].set_title('Predict:'+str(predicted_num))
           ax[i,j].axis('off')