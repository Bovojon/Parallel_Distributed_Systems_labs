// James, Aakarsh and I discussed ideas together for this assignment.
// However, each of us wrote our own code and program.
import java.io.IOException;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.io.Text;
import java.util.StringTokenizer;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;

public class MaxMapper extends Mapper<Object, Text, Text, Text>{
	public boolean is_int(String number) {
	    try {
	        Integer.parseInt(number);
	        return true;
	    }
	    catch( Exception e ) {
	        return false;
	    }
	}
	public void map(Object key, Text val, Context context) throws IOException, InterruptedException {
		String[] strTk;
		String output;
		StringTokenizer itr = new StringTokenizer(val.toString());
		while (itr.hasMoreTokens()){
			strTk = itr.nextToken().split(";");
			if (strTk.length == 2) {
				if (is_int(strTk[1])){
					output = strTk[0]+","+strTk[1];
					context.write(new Text("output"), new Text(output));
				}
			}
		}
	}
}
