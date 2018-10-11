import numpy as np

# as demolish is a 2D collision detection software
# we only have to check the distance between line segs

# this is just an implementation of the well used
# penalty method for calculating the minimum distance
# between simplices in computational geometry.


# this will need to be implmented in C++, but having a 
# nice simple code in python will benefit us later on.

'''

hf - this is the hessian of f
gf - this is the gradient of f
h  - a vector of contraints
dh - differentiate 
we are minimising over two parameters, x[0], x[1]

give the vertices of the edge points of the line segment
as 
'''

def minimiseDistanceBetweenLineSegments(A,B,C,D,epsilon,tol):
    AB = B-A
    CD = D-C
    hf = np.array([[2*np.dot(AB,AB),-2*np.dot(AB,CD)],
                   [-2*np.dot(AB,CD), 2*np.dot(CD,CD)]])
    x = [0.33,0.1]
    for i in range(100):
        gf = np.array([-2*np.dot(CD,AB)*x[1] + 2*x[0]*np.dot(AB,AB),
                       -2*np.dot(CD,AB)*x[0] + 2*x[1]*np.dot(CD,CD)])
        h = np.array([-x[0],-x[1],x[0]-1,x[1]-1])
        dh = np.array([[-1,0,1,0],[0,-1,0,1]])
        mask = (h>=0).astype('int')
        dmax = dh*np.vstack([mask,mask])
        grad = gf + eps*np.dot(dmax,np.maximum(np.zeros(4),h))
        hes = hf + eps*np.matmul(dmax,dmax.transpose()) + np.eye(2)/(eps * eps)
        dx = np.linalg.solve(hes,grad);
        DX = np.dot(AB,dx[0])
        DY = np.dot(CD,dx[1])
        error = np.sqrt(np.dot(DX,DX) + np.dot(DY,DY))
        x = x-dx
        print x
        if(error<tol):
            break
    return x

A = np.array([1,2])
B = np.array([2,4])
C = np.array([3,2])
D = np.array([3,4])

eps = 0.001;tol = 0.0001

print(minimiseDistanceBetweenLineSegments(A,B,C,D,eps,tol))



