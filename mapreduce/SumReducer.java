// James, Aakarsh and I discussed ideas together for this assignment.
// However, each of us wrote our own code and program.
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;

public class SumReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
	private IntWritable resultIntW = new IntWritable();
	public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
		int total=0;
		for(IntWritable val : values) {
			total+=val.get();
		}
		String reducer_key=key.toString();
		resultIntW.set(total);
		context.write(new Text(reducer_key), resultIntW);
	}
}
