import { StatusBar } from 'expo-status-bar';
import React from 'react';
import { StyleSheet, Text, View, SafeAreaView, TouchableOpacity} from 'react-native';
import Constants from 'expo-constants';
import { getAccessToken } from '../../utils/auth.js';
import ProgressBar from '../ProgressBar.js';

const server_add = Constants.manifest.extra.apiUrl;

export default class HomeScreen extends React.Component{
    state = {
        Trainee_progress: 0, 
        Trainee_total: 0,
        Associate_progress: 0,
        Associate_total: 0,
        Partner_progress: 0,
        Partner_total: 0,
    };
    componentDidMount(){
        getAccessToken().then(accessToken => 
            fetch(server_add + '/calculateProgressBar', {
                "headers": {
                    "Authorization": "Bearer " + accessToken
                }
        }))
        .then(async response => {
            let data = await response.json();
            console.log(data);
            this.setState({
                Trainee_progress: 7,
                // data.Trainee_complete,
                Trainee_total: data.Trainee_total,
                Associate_progress: data.Associate_outcome,
                Associate_total: data.Associate_total,
                Partner_progress: 9, // should change to *data.Partner_sum* data.Associate_sum
                Partner_total: data.Partner_total,
            })
        })
        .catch(function (error) {
            // TODO: error message 
            // no progress to display, 
            // component
            console.log(error);
        });
    }

    render(){
        let T_displayBlock, T_displayBlockText, T_ProgressBarDisplay, T_ProgressBarText, T_ProgressBarFill;
        let A_displayBlock, A_displayBlockText, A_ProgressBarDisplay, A_ProgressBarText, A_ProgressBarFill;
        let P_displayBlock, P_displayBlockText, P_ProgressBarDisplay, P_ProgressBarText, P_ProgressBarFill;
        if (this.state.Trainee_progress == this.state.Trainee_total){
            T_displayBlock = styles.ongoingBlock;
            T_displayBlockText = styles.ongoingBlockText;
            // T_ProgressBarDisplay = styles.completedBlockProgressBar;
            // T_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            // T_ProgressBarFill = styles.completedBlockProgressBarFill;
            
            // TODO
            A_displayBlock = styles.todoBlockBlock;
            A_displayBlockText = styles.todoBlockText;
            // A_ProgressBarDisplay = styles.completedBlockProgressBar;
            // A_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            // A_ProgressBarFill = styles.completedBlockProgressBarFill;

            P_displayBlock = styles.todoBlockBlock;
            P_displayBlockText = styles.todoBlockText;
            // P_ProgressBarDisplay = styles.completedBlockProgressBar;
            // P_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            // P_ProgressBarFill = styles.completedBlockProgressBarFill;
        }

        if (this.state.Partner_progress == this.state.Partner_total) { // everything is completed 
            T_displayBlock = styles.completedBlock;
            T_displayBlockText = styles.completedBlockText;
            T_ProgressBarDisplay = styles.completedBlockProgressBar;
            T_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            T_ProgressBarFill = styles.completedBlockProgressBarFill;
            
            A_displayBlock = styles.completedBlock;
            A_displayBlockText = styles.completedBlockText;
            A_ProgressBarDisplay = styles.completedBlockProgressBar;
            A_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            A_ProgressBarFill = styles.completedBlockProgressBarFill;

            P_displayBlock = styles.completedBlock;
            P_displayBlockText = styles.completedBlockText;
            P_ProgressBarDisplay = styles.completedBlockProgressBar;
            P_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            P_ProgressBarFill = styles.completedBlockProgressBarFill;
        } else if(this.state.Associate_progress == this.state.Associate_total){
            // TODO
            T_displayBlock = styles.completedBlock;
            T_displayBlockText = styles.completedBlockText;
            T_ProgressBarDisplay = styles.completedBlockProgressBar;
            T_ProgressBarDisplayText = styles.completedBlockProgressBarText;
            T_ProgressBarFill = styles.completedBlockProgressBarFill;
        } else {

        }
           
        return(
        <SafeAreaView style={styles.container}>
        <TouchableOpacity 
            style={T_displayBlock} 
            onPress={() => this.props.navigation.navigate('Trainee Pod')}
        >
                <Text style={T_displayBlockText}> Trainee </Text>
            <ProgressBar style={T_ProgressBarDisplay} Textstyle={T_ProgressBarText} fill={T_ProgressBarFill} progress={this.state.Trainee_progress} total_outcomes={this.state.Trainee_total} />
        </TouchableOpacity>
      
        <TouchableOpacity className="sidebar"
            style={A_displayBlock} 
            onPress={() => this.props.navigation.navigate('Associate Pod')}
        >
            <Text style={A_displayBlockText}> Associate </Text>
            <ProgressBar style={A_ProgressBarDisplay} Textstyle={A_ProgressBarText} fill={A_ProgressBarFill} progress={this.state.Associate_progress} total_outcomes={this.state.Associate_total} />
        </TouchableOpacity>
    
        <TouchableOpacity 
            style={P_displayBlock} 
            onPress={() => this.props.navigation.navigate('Partner Pod')}
        >                
            <Text style={P_displayBlockText}> Partner </Text>
            <ProgressBar style={P_ProgressBarDisplay} Textstyle={P_ProgressBarText} fill={P_ProgressBarFill} progress={this.state.Partner_progress} total_outcomes={this.state.Partner_total} />
        </TouchableOpacity>
    </SafeAreaView>);
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#fff',
        alignItems: 'center',
        justifyContent: 'center',
    },
    completedBlock: {
        marginTop: 20,
        width: '100%',
        height: 220,
        backgroundColor: '#ececec',
        borderColor: 'white',
        borderWidth: 1,
        borderRadius: 1,
        alignItems: 'center',
        justifyContent: 'center',
    },
    completedBlockText: {
        fontSize: 40,
        // fontFamily: 'Roboto',
        color: '#27b48f',
        fontWeight: 'bold',
        textAlign: 'center',
    },
    completedBlockProgressBar: {
        flexDirection: 'row',
        height: 20,
        width: 250,
        backgroundColor: 'white',
        borderColor: '#27b48f', 
        borderWidth: 2,
        borderRadius: 10,
    },
    completedBlockProgressBarText: {
        color: '#27b48f',
        fontFamily: 'Roboto',
    },

    // ONGOING Block
    ongoingBlock: {
        marginTop: 20,
        width: '100%',
        height: 220,
        backgroundColor: '#27b48f',
        borderColor: 'white',
        borderWidth: 1,
        borderRadius: 1,
        alignItems: 'center',
        justifyContent: 'center',
    },
    ongoingBlockText: {
        fontSize: 40,
        fontFamily: 'Roboto',
        color: '#ffffff',
        fontWeight: 'bold',
        textAlign: 'center',
    },

    // TODO Block
    todoBlock: {
        marginTop: 20,
        width: '100%',
        height: 220,
        backgroundColor: '#ececec',
        borderColor: 'white',
        borderWidth: 1,
        borderRadius: 1,
        alignItems: 'center',
        justifyContent: 'center',
    },
    todoBlockText: {
        fontSize: 40,
        fontFamily: 'Roboto',
        color: '#9e9e9e',
        fontWeight: 'bold',
        textAlign: 'center',
    },  
});