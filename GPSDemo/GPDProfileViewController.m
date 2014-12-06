//
//  GPDProfileViewController.m
//  GPShopper-iOS
//
//  Created by Matthew Reed on 10/28/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDProfileViewController.h"
#import "GPDLoginViewController.h"
#import <GPShopper/GPShopper.h>

@interface GPDProfileViewController () <UIAlertViewDelegate>
{
    SCProfile *profile;
    SCSession *session;
    SCRegistrationState *state;
}

@property (strong, nonatomic) IBOutlet UILabel *firstNameLabel;
@property (strong, nonatomic) IBOutlet UILabel *lastNameLabel;
@property (strong, nonatomic) IBOutlet UILabel *emailLabel;
@property (strong, nonatomic) IBOutlet UIButton *loginLogoutButton;

@end

@implementation GPDProfileViewController

@synthesize firstNameLabel;
@synthesize lastNameLabel;
@synthesize emailLabel;
@synthesize loginLogoutButton;


- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        profile = [SCProfile defaultProfile];
        session = [SCSession defaultSession];
        state = [SCRegistrationState defaultState];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    if (profile.fetched) {
        firstNameLabel.hidden = NO;
        lastNameLabel.hidden = NO;
        emailLabel.hidden = NO;
        firstNameLabel.text = profile.firstName;
        lastNameLabel.text = profile.lastName;
        emailLabel.text = profile.email;
        [loginLogoutButton setTitle:@"Logout" forState:UIControlStateNormal];
    } else {
        [loginLogoutButton setTitle:@"Login" forState:UIControlStateNormal];
    }
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sessionUpdated) name:@"scsession_updated" object:session];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}

- (void)sessionUpdated {
    if (!session.exists) {
        [profile clear];
        [state clear];
        firstNameLabel.hidden = YES;
        lastNameLabel.hidden = YES;
        emailLabel.hidden = YES;
        firstNameLabel.text = nil;
        lastNameLabel.text = nil;
        emailLabel.text = nil;
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"You have been logged out" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
    } else {
        [loginLogoutButton setTitle:@"Logout" forState:UIControlStateNormal];
    }
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"scsession_updated" object:session];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 1) {
        [session destroy];
        [loginLogoutButton setTitle:@"Login" forState:UIControlStateNormal];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)loginLogoutButtonPressed:(id)sender {
    if (session.exists) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"Log out?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Logout", nil];
        [alert show];
    } else {
        GPDLoginViewController *vc = [[GPDLoginViewController alloc] initWithNibName:@"GPDLoginViewController" bundle:nil];
        vc.title = @"Login";
        UINavigationController *nc = [[UINavigationController alloc] initWithRootViewController:vc];
        [self presentViewController:nc animated:YES completion:nil];
    }
}

@end
