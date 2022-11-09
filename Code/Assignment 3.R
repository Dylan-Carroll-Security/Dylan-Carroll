#Dylan Carroll
#-----------
#------------
#---------


#simplified = cos(2t) - original function( 0(t) ) 
#0t = 3 therefore (0,3) is given point 
student.ode.euler <- function(st,exactt){
  yTemp = 3
  xTemp = 0 
  error = 0
  x = xTemp
  y = yTemp
  
 
  step = get.steps(st)
  
  print(paste("steps = ", step))
  
  for(i in 1:step){
    
  
    yTemp <- yTemp + st * ( (cos(2*xTemp)) - (0.2*cos(2*xTemp) + 0.4*sin(2*xTemp) + 2.8*exp(-xTemp)))
    
    xTemp <- xTemp + st #increment x values by the h value 
    i = i + 1
    x[i] = xTemp ## here the xTemp and yTemp are the one of the recent step, to add into vector and used in next step as last is needed

    y[i] = yTemp
    if(exactt != 5){
    exact[i] = student.ode.exact(x[i])
    }
    else{
      exact[i] = student.ode.exact(x[i])
    }
    error[i] = student.ode.error(y[i],exact[i]) 
  }
 
  return(data.frame(exact,y))
}

student.ode.exact <- function(x){
  exact = (0.2 *cos(x*0.1) + 0.4 *sin(x*0.1) + 2.8 *exp(-0.1))  
  
  
  
  return(exact)

}
student.ode.error <- function(measured,real){
  error = (measured-real) 
  if(error < 0){
    error = error * -1
  }
  error = error / real
  
  error = error * 100 #change from decimal 
  return(error)
}

get.steps <- function(x){
  
  #on paper i just took 3 and divide by h
  if(x==0.8){
    return(4) #    Rounded 3.75 up to 4.... as 3 will not divide into 0.8 for int number of steps :/ 
  }else if(x==0.2){
    return(15)
  }else if(x==0.05){
    return(60)
  }
  
  
}
student.ode.rk4 <- function(x){
  h = x

  step =get.steps(h)
  if(step==4){
    step=3
  }
  finY <-list(length(step))
  finX <-list(length(step))
  yTemp = c()
  xTemp = c()
  yTemp = 3
  xTemp = 0
  y = yTemp
  x = xTemp
  #iterations
  i = 0
  z = 0
  for(i in 1:step){
  i = h * (  (0.2*cos(2*xTemp) + 0.4*sin(2*xTemp) + 2.8*exp(-xTemp)))

  
  i1 = h *  ( (0.2*cos(2*xTemp+h/2) + 0.4*sin(2*xTemp+h/2) + 2.8*exp(-xTemp+h/2)))
 # i1 = i1+ ( (0.2*cos(2*yTemp+(1/2)*i*h) + 0.4*sin(2*yTemp+(1/2)*i*h) + 2.8*exp(-yTemp+(1/2)*i*h))) #second ones are the for the y portion of the 
  
  
  i2 = h *  ( (0.2*cos(2*xTemp+h/2) + 0.4*sin(2*xTemp+h/2) + 2.8*exp(-xTemp+h/2)))  
 # i2 = i2+  (  (0.2*cos(2*yTemp+(1/2)*i1*h) + 0.4*sin(2*yTemp+(1/2)*i1*h) + 2.8*exp(-yTemp+(1/2)*i*h)))
  
  
  
  i3 = h *   ( (0.2*cos(2*xTemp+h) + 0.4*sin(2*xTemp+h) + 2.8*exp(-xTemp+h)))   
 # i3 =  i3 + (  (0.2*cos(2*xTemp+h*i2) + 0.4*sin(2*xTemp+h*i2) + 2.8*exp(-xTemp+h*i2)))   
  
  
  
  yTemp <- yTemp + (h*(1/6))*(i + 2*i1 + 2*i2 + i3 )
  
  xTemp <- xTemp + h
  
  finX[i]=xTemp
  finY[i]=yTemp
  print("State")
 print(yTemp)
 print(xTemp)

  }
  print("End")
  print(yTemp)
  print(xTemp)
  return(data.frame(xTemp,yTemp))
}


  #plot using eulers
  plot(student.ode.euler(0.8,5),col = "blue",pch = 2)
  points(student.ode.euler(0.2,1),col = "red",pch=21)
  points(student.ode.euler(0.05,1),col = "green",pch = 12)

  
  
  #plot using 4th order runge kunta 
 # plot(student.ode.kutta(0.2),col = "blue",pch = 2)
  #points(student.ode.kutta(0.8),col = "red",pch=21)
  #points(student.ode.kutta(0.05),col = "green",pch = 12)
 
  #points( (cos(2*xTemp)) - (0.2*cos(2*xTemp) + 0.4*sin(2*xTemp) + 2.8*exp(-xTemp)) ,col = "brown",pch=4) # attempt to plot
  

  