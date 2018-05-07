// James, Aakarsh and I discussed ideas together for this assignment.
// However, each of us wrote our own code and program.
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;

public class SumMapper extends Mapper<Object, Text, Text, IntWritable>{
	public boolean is_int(String num){
	    try {
	        Integer.parseInt(num);
	        return true;
	    }
	    catch( Exception e ) {
	        return false;
	    }
	}
	private IntWritable intWritableObj = new IntWritable();
	public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
		String[] strTk;
		StringTokenizer tokenizer = new StringTokenizer(value.toString());
		while (tokenizer.hasMoreTokens()){
			strTk = tokenizer.nextToken().split(",");
			if (is_int(strTk[3])){
				if (Integer.parseInt(strTk[3]) == 4){
					intWritableObj.set(1);
				} else {
					intWritableObj.set(0);
				}
			} else {
				intWritableObj.set(0);
			}
			context.write(new Text(strTk[2]), intWritableObj);
		}
	}
}
