// James, Aakarsh and I discussed ideas together for this assignment.
// However, each of us wrote our own code and program.
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.IntWritable;

public class MaxReducer extends Reducer<Text, Text, Text, Text> {
	public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
		int maximum =0;
		String[] strTk;
		String output_string = "All the businesses with maximum 4 stars reviews are ";
		for(Text val : values) {
			strTk = val.toString().split(",");
			if (strTk.length >= 2) {
				if (maximum < Integer.parseInt(strTk[1])) {
					maximum = Integer.parseInt(strTk[1]);
					output_string="";
				}
				if (maximum==Integer.parseInt(strTk[1])) {
					output_string = output_string+strTk[0]+",";
				}
			} else {
				output_string+=val.toString();
			}
		}
		context.write(new Text("output"), new Text(output_string));
	}
}
