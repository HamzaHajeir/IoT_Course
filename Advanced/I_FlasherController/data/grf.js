class graph{
	decorate(){
		var incr=this.maxY/this.ticks;
		var c=this.ctx;
	
		c.fillStyle="#000";
		c.font = '8px sans-serif';	
		c.beginPath();
		for(var i=0;i<this.ticks-1;i++){
			var y=incr*(i+1);
			var plotY=this.norm(y);
			c.moveTo(0,plotY);
			c.lineTo(10,plotY);
			c.fillText(Math.round(y),12,plotY);	
		}
		c.stroke();
	}	
	
	drawFrame(){
		var c=this.ctx;
		c.fillStyle="#fff";
		c.fillRect(0,0,this.width,this.height);
		c.strokeStyle="#000";
		c.strokeRect(0,0,this.width,this.height);		
		this.decorate();
	}	
	constructor(ele,maxY,base,ticks,dp){
		this.ele=ele;
		this.maxY=maxY;
		this.base=base;
		this.ticks=ticks;
		this.dp=dp;		
		var g=document.getElementById(ele);
		var c=this.ctx=g.getContext("2d");
		this.height=g.height;
		this.width=g.width;
		this.nPoints=this.width/base;
		this.points=[];
		this.strikes=[];
		for(var i=0;i<this.nPoints;i++)	this.points[i]=0;		
	}
	
	strike(c){
		this.strikes.push({c: c, n: this.width});	
	}
	
	norm(v){
		var h=this.height;
		return h-((v/this.maxY)*h);
	}

	plot(v){
		this.points.shift();
		this.points.push(v);
		
		this.drawFrame();
		var x=0;
		var y=0;	
		this.sigma=0;
		var slide=parseInt(this.base);
		var c=this.ctx;
		c.strokeStyle="#00f";		
		
		c.beginPath();		
		for(var i=0;i<this.nPoints;i++){
			y=this.points[i];
			this.sigma+=parseInt(y);
			c.lineTo(x,this.norm(y));
			x+=slide;
		}
		c.stroke();
		
		var avg=this.sigma/this.nPoints;
		c.beginPath();		
			c.strokeStyle="#f00";
			c.setLineDash([5, 5]);
			c.moveTo(0,this.norm(avg));
			c.lineTo(this.width,this.norm(avg));
		c.stroke();
		
		c.setLineDash([]);
		c.fillStyle="#f00";
		c.font = '8px sans-serif';
		c.fillText(avg.toFixed(this.dp),this.width / 2 ,this.norm(avg) - 3);
		
		for(var i=0;i<this.strikes.length;i++){
			this.strikes[i].n-=slide;
			if(this.strikes[i].n<slide) this.strikes.shift();
			else {
				c.beginPath();		
					c.strokeStyle=this.strikes[i].c;
					c.moveTo(this.strikes[i].n,0);
					c.lineTo(this.strikes[i].n,this.height);
				c.stroke();						
			}
		}
	}				
}
