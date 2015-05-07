//
//  GPDMoreViewController.m
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDMoreViewController.h"

@interface GPDMoreViewController () <SCBeaconDeviceManagerDelegate, UIAlertViewDelegate>

@end

@implementation GPDMoreViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"More";
    
    /* ----------------- RASHAD EDITS --------------------- */
    
    [self beaconsAlertOptionToggle];
    
    /* --------------------- END --------------------------- */
}


#pragma mark UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.viewControllers.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *reuseID = @"more_cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseID];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseID];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    UIViewController *vc = self.viewControllers[indexPath.row];
    cell.textLabel.text = vc.title;
    return cell;
}
#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    UIViewController *vc = self.viewControllers[indexPath.row];
    [self.navigationController pushViewController:vc animated:YES];
}

/* ----------------- RASHAD EDITS --------------------- */

- (void)beaconsAlertOptionToggle
{
    NSString *alertTitle = [[NSString alloc] initWithFormat:@"iBeacons Opt-In"];
    NSString *alertMessage;
    if ([SCBeaconDeviceManager isOptedIn]) {
        alertMessage = [[NSString alloc] initWithFormat:@"Your device has iBeacons turned ON, do you want to continue running iBeacons?"];
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:@"Leave ON"
                                              otherButtonTitles:@"Turn OFF", nil];
        alert.tag = 1;
        [alert show];
    } else {
        alertMessage = [[NSString alloc] initWithFormat:@"Your device has iBeacons turned OFF, do you want to turn iBeacons ON?"];
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:@"Leave OFF"
                                              otherButtonTitles:@"Turn ON", nil];
        alert.tag = 2;
        [alert show];
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView.tag == 1) {
        if (buttonIndex == 1) {
            [SCBeaconDeviceManager optIn:NO];
            NSLog(@"Opted-OUT");
        } else if (buttonIndex == 0) {
            NSLog(@"Leave ON");
        }
    
    
    } else if (alertView.tag ==2){
        
        if (buttonIndex == 1) {
            [SCBeaconDeviceManager optIn:YES];
            NSLog(@"Opted-IN");
        } else if (buttonIndex == 0) {
            NSLog(@"Leave OFF");
        }
    }
}

/* ---------------------- END -------------------------- */

@end
